#pragma once

/**
 * @file core.h
 * @brief The core header file that contains the core subsystems and utilities for JAGE.
 */

#include "jgpch.h"

/**
 * (use CTRL + F or the corresponding finding text tool in your text editor for the sections below)
 * CODE SECTIONS:
 * 
 * - MACRO FOR API EXPORT DEFINITIONS
 * - MACRO FOR SUPPRESSING WARNINGS IN CODE
 * - MACRO FOR SHIFT-LEFT BIT OPERATION
 * 
 * - STRING TO ID CONVERSION
 * - INITIALISATION/DESTRUCTION DEFINITIONS
 * - TIMING DEFINITIONS
 * - LOGGER DEFINITIONS
 * - INPUT DEFINITIONS
 * - LOGICAL PATH DEFINITIONS
 * - URI DEFINITIONS
 * - CORE EVENT DEFINITIONS
 * - MACRO FOR EVENTS DEFINITIONS
 * - APPLICATION/WINDOW EVENT DEFINITIONS
 * - KEY/CHAR EVENT DEFINITIONS
 * - MOUSE EVENT DEFINITIONS
 */

/**
 * 
 * 
 * MACRO FOR API EXPORT DEFINITIONS
 * 
 * 
 */
#ifdef _WIN32
#   ifdef JAGE_EXPORT
#       define JAGE_API __declspec(dllexport)
#   else
#       define JAGE_API __declspec(dllimport)
#   endif
#elif defined(__clang__) || defined(__GNUC__) && __GNUC__ >= 4
#   define JAGE_API __attribute__((visibility("default")))
#else
#   define JAGE_API
#endif

/**
 * 
 * 
 * MACRO FOR SUPPRESSING WARNINGS IN CODE
 * 
 * 
 */
#ifdef _MSC_VER
#   define DISABLE_WARNING_PUSH __pragma(warning(push))
#   define DISABLE_WARNING_POP __pragma(warning(pop))
#   define DISABLE_WARNING_MSVC(w) __pragma(warning(disable : w))
#   define DISABLE_WARNING_GCC_CLANG(w)
#elif defined(__clang__) || defined(__GNUC__)
#   define DO_PRAGMA(X) _Pragma(#X)
#   define DISABLE_WARNING_PUSH DO_PRAGMA(GCC diagnostic push)
#   define DISABLE_WARNING_POP DO_PRAGMA(GCC diagnostic pop)
#   define DISABLE_WARNING_MSVC(w)
#   define DISABLE_WARNING_GCC_CLANG(w) DO_PRAGMA(GCC diagnostic ignored w)
#else
#   define DISABLE_WARNING_PUSH
#   define DISABLE_WARNING_POP
#   define DISABLE_WARNING_MSVC(w)
#   define DISABLE_WARNING_GCC_CLANG(w)
#endif

/**
 * 
 * 
 * STRING TO ID CONVERSION
 * 
 * 
 */
namespace JAGE
{
    u64 str_to_ID(std::string_view str);
}

/**
 * 
 * 
 * INITIALIZATION/DESTRUCTION DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    JAGE_API void Init(int argc, char** argv);
    JAGE_API void Destroy();
}

/**
 * 
 * 
 * TIMING DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    namespace Time
    {
        constexpr u64 SECONDS_TO_NANO { 1000000000 };
        constexpr u64 SECONDS_TO_MILLI { 1000 };
        constexpr u64 MILLI_TO_NANO { 1000000 };

        JAGE_API void SetTargetFPS(unsigned fps);

        JAGE_API float ElapsedTime();
        JAGE_API float DeltaTime();
    }
}

/**
 * 
 * 
 * LOGGER DEFINITIONS
 * 
 * 
 */
#include <spdlog/spdlog.h>

namespace JAGE
{
    /**
     * @class AppLogger
     * 
     * @brief The `AppLogger` class used to log game operations.
     *
     * Both JAGE and the game use `spdlog` as its logging backend. `spdlog` is templated, which means either the JAGE's
     * API has to also expose `spdlog`'s templates (which lets the game bypass JAGE's API altogether if it wants), or
     * hide them via pointer-to-implementation (which then means that JAGE has to implement each and every template
     * instantiation possible when using `spdlog`). The former was chose to prioritise flexibility.
     */
    class JAGE_API AppLogger
    {
    private:
        inline static std::shared_ptr<spdlog::logger> logger { nullptr };
    public:
        static void Init(spdlog::level::level_enum app_level);

        static void Trace(std::string_view msg)      { logger->trace(msg); }
        static void Debug(std::string_view msg)      { logger->debug(msg); }
        static void Info(std::string_view msg)       { logger->info(msg); }
        static void Warn(std::string_view msg)       { logger->warn(msg); }
        static void Error(std::string_view msg)      { logger->error(msg); }
        static void Critical(std::string_view msg)   { logger->critical(msg); }

        template<typename... Args>
        static void Trace(std::string_view log, Args &&... args)
        { logger->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        static void Debug(std::string_view log, Args &&... args)
        { logger->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        static void Info(std::string_view log, Args &&... args)
        { logger->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        static void Warn(std::string_view log, Args &&... args)
        { logger->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        static void Error(std::string_view log, Args &&... args)
        { logger->error(log, std::forward<Args>(args)...); }
        template<typename... Args>
        static void Critical(std::string_view log, Args &&... args)
        { logger->critical(log, std::forward<Args>(args)...); }
    };

    #define APP_MSG_TRACE(MSG)      JAGE::AppLogger::Trace(MSG)
    #define APP_MSG_DEBUG(MSG)      JAGE::AppLogger::Debug(MSG)
    #define APP_MSG_INFO(MSG)       JAGE::AppLogger::Info(MSG)
    #define APP_MSG_WARN(MSG)       JAGE::AppLogger::Warn(MSG)
    #define APP_MSG_ERROR(MSG)      JAGE::AppLogger::Error(MSG)
    #define APP_MSG_CRITICAL(MSG)   JAGE::AppLogger::Critical(MSG); std::abort()

    #define APP_LOG_TRACE(LOG, ...)     JAGE::AppLogger::Trace(LOG, __VA_ARGS__)
    #define APP_LOG_DEBUG(LOG, ...)     JAGE::AppLogger::Debug(LOG, __VA_ARGS__)
    #define APP_LOG_INFO(LOG, ...)      JAGE::AppLogger::Info(LOG, __VA_ARGS__)
    #define APP_LOG_WARN(LOG, ...)      JAGE::AppLogger::Warn(LOG, __VA_ARGS__)
    #define APP_LOG_ERROR(LOG, ...)     JAGE::AppLogger::Error(LOG, __VA_ARGS__)
    #define APP_LOG_CRITICAL(LOG, ...)  JAGE::AppLogger::Critical(LOG, __VA_ARGS__); std::abort()
}

/**
 * 
 * 
 * INPUT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    namespace Input
    {
        enum class KeyCode : u16
        {
            UNKNOWN = 0,

            A = 4,
            B, C, D, E, F,
            G, H, I, J, K,
            L, M, N, O, P,
            Q, R, S, T, U,
            V, W, X, Y, Z,

            _1, _2, _3, _4, _5, _6, _7, _8, _9, _0,

            SPACE, COMMA, PERIOD, FORWARDSLASH,
            SEMICOLON, APOSTROPHE,
            LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET, BACKSLASH,
            GRAVE_ACCENT, MINUS, EQUAL,

            ENTER, ESCAPE, BACKSPACE, TAB, CAPS_LOCK,

            LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW,

            LEFT_SHIFT, RIGHT_SHIFT,
            LEFT_CONTROL, RIGHT_CONTROL,
            LEFT_ALT, RIGHT_ALT,

            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

            KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9, KP0
        };

        enum class MouseButton : u8
        {
            UNKNOWN = 0, _1, _2, _3, _4, _5
        };

        enum class Action : u8
        {
            PRESSED = 0, RELEASED, REPEATED
        };

        enum class Modifier : u8
        {
            NONE        = 0,
            SHIFT       = 1 << 0,
            CONTROL     = 1 << 1,
            ALT         = 1 << 2,
        };

        enum class CursorMode : u8 { NORMAL = 0, DISABLED, HIDDEN };

        JAGE_API u8 operator&(Modifier lhs, Modifier rhs);
        JAGE_API u8 operator|(Modifier lhs, Modifier rhs);
        JAGE_API u8 operator&(u8 lhs, Modifier rhs);
        JAGE_API u8 operator|(u8 lhs, Modifier rhs);
        JAGE_API u8 operator&(Modifier lhs, u8 rhs);
        JAGE_API u8 operator|(Modifier lhs, u8 rhs);

        JAGE_API bool IsKeyPressed(KeyCode key);
        JAGE_API bool IsKeyReleased(KeyCode key);
        JAGE_API bool IsMouseButtonPressed(MouseButton button);
        JAGE_API bool IsMouseButtonReleased(MouseButton button);

        JAGE_API void SetCursorMode(CursorMode mode);
        JAGE_API CursorMode GetCursorMode();

        JAGE_API float GetMousePositionX();
        JAGE_API float GetMousePositionY();
        JAGE_API float GetMousePositionDeltaX();
        JAGE_API float GetMousePositionDeltaY();

        JAGE_API std::string to_string(KeyCode key);
        JAGE_API std::string to_string(Action action);
        JAGE_API std::string to_string(MouseButton button);
        JAGE_API std::string to_string(int mods);
        JAGE_API std::string to_string(CursorMode mode);

        JAGE_API std::ostream& operator<<(std::ostream& os, const KeyCode& key);
        JAGE_API std::ostream& operator<<(std::ostream& os, const Action& action);
        JAGE_API std::ostream& operator<<(std::ostream& os, const MouseButton& button);
        JAGE_API std::ostream& operator<<(std::ostream& os, const int& mods);
        JAGE_API std::ostream& operator<<(std::ostream& os, const CursorMode& mode);

        #define JAGE_KEY_UNKNOWN JAGE::Input::KeyCode::UNKNOWN
        #define JAGE_KEY_A JAGE::Input::KeyCode::A
        #define JAGE_KEY_B JAGE::Input::KeyCode::B
        #define JAGE_KEY_C JAGE::Input::KeyCode::C
        #define JAGE_KEY_D JAGE::Input::KeyCode::D
        #define JAGE_KEY_E JAGE::Input::KeyCode::E
        #define JAGE_KEY_F JAGE::Input::KeyCode::F
        #define JAGE_KEY_G JAGE::Input::KeyCode::G
        #define JAGE_KEY_H JAGE::Input::KeyCode::H
        #define JAGE_KEY_I JAGE::Input::KeyCode::I
        #define JAGE_KEY_J JAGE::Input::KeyCode::J
        #define JAGE_KEY_K JAGE::Input::KeyCode::K
        #define JAGE_KEY_L JAGE::Input::KeyCode::L
        #define JAGE_KEY_M JAGE::Input::KeyCode::M
        #define JAGE_KEY_N JAGE::Input::KeyCode::N
        #define JAGE_KEY_O JAGE::Input::KeyCode::O
        #define JAGE_KEY_P JAGE::Input::KeyCode::P
        #define JAGE_KEY_Q JAGE::Input::KeyCode::Q
        #define JAGE_KEY_R JAGE::Input::KeyCode::R
        #define JAGE_KEY_S JAGE::Input::KeyCode::S
        #define JAGE_KEY_T JAGE::Input::KeyCode::T
        #define JAGE_KEY_U JAGE::Input::KeyCode::U
        #define JAGE_KEY_V JAGE::Input::KeyCode::V
        #define JAGE_KEY_W JAGE::Input::KeyCode::W
        #define JAGE_KEY_X JAGE::Input::KeyCode::X
        #define JAGE_KEY_Y JAGE::Input::KeyCode::Y
        #define JAGE_KEY_Z JAGE::Input::KeyCode::Z

        #define JAGE_KEY_1 JAGE::Input::KeyCode::_1
        #define JAGE_KEY_2 JAGE::Input::KeyCode::_2
        #define JAGE_KEY_3 JAGE::Input::KeyCode::_3
        #define JAGE_KEY_4 JAGE::Input::KeyCode::_4
        #define JAGE_KEY_5 JAGE::Input::KeyCode::_5
        #define JAGE_KEY_6 JAGE::Input::KeyCode::_6
        #define JAGE_KEY_7 JAGE::Input::KeyCode::_7
        #define JAGE_KEY_8 JAGE::Input::KeyCode::_8
        #define JAGE_KEY_9 JAGE::Input::KeyCode::_9
        #define JAGE_KEY_0 JAGE::Input::KeyCode::_0

        #define JAGE_KEY_SPACE                  JAGE::Input::KeyCode::SPACE
        #define JAGE_KEY_COMMA                  JAGE::Input::KeyCode::COMMA
        #define JAGE_KEY_PERIOD                 JAGE::Input::KeyCode::PERIOD
        #define JAGE_KEY_FORWARDSLASH           JAGE::Input::KeyCode::FORWARDSLASH
        #define JAGE_KEY_SEMICOLON              JAGE::Input::KeyCode::SEMICOLON
        #define JAGE_KEY_APOSTROPHE             JAGE::Input::KeyCode::APOSTROPHE
        #define JAGE_KEY_LEFT_SQUARE_BRACKET    JAGE::Input::KeyCode::LEFT_SQUARE_BRACKET
        #define JAGE_KEY_RIGHT_SQUARE_BRACKET   JAGE::Input::KeyCode::RIGHT_SQUARE_BRACKET
        #define JAGE_KEY_BACKSLASH              JAGE::Input::KeyCode::BACKSLASH
        #define JAGE_KEY_GRAVE_ACCENT           JAGE::Input::KeyCode::GRAVE_ACCENT
        #define JAGE_KEY_MINUS                  JAGE::Input::KeyCode::MINUS
        #define JAGE_KEY_EQUAL                  JAGE::Input::KeyCode::EQUAL

        #define JAGE_KEY_ENTER      JAGE::Input::KeyCode::ENTER
        #define JAGE_KEY_ESCAPE     JAGE::Input::KeyCode::ESCAPE
        #define JAGE_KEY_BACKSPACE  JAGE::Input::KeyCode::BACKSPACE
        #define JAGE_KEY_TAB        JAGE::Input::KeyCode::TAB
        #define JAGE_KEY_CAPS_LOCK  JAGE::Input::KeyCode::CAPS_LOCK

        #define JAGE_KEY_LEFT_ARROW     JAGE::Input::KeyCode::LEFT_ARROW
        #define JAGE_KEY_RIGHT_ARROW    JAGE::Input::KeyCode::RIGHT_ARROW
        #define JAGE_KEY_UP_ARROW       JAGE::Input::KeyCode::UP_ARROW
        #define JAGE_KEY_DOWN_ARROW     JAGE::Input::KeyCode::DOWN_ARROW

        #define JAGE_KEY_LEFT_SHIFT     JAGE::Input::KeyCode::LEFT_SHIFT
        #define JAGE_KEY_RIGHT_SHIFT    JAGE::Input::KeyCode::RIGHT_SHIFT
        #define JAGE_KEY_LEFT_CONTROL   JAGE::Input::KeyCode::LEFT_CONTROL
        #define JAGE_KEY_RIGHT_CONTROL  JAGE::Input::KeyCode::RIGHT_CONTROL
        #define JAGE_KEY_LEFT_ALT       JAGE::Input::KeyCode::LEFT_ALT
        #define JAGE_KEY_RIGHT_ALT      JAGE::Input::KeyCode::RIGHT_ALT

        #define JAGE_KEY_F1     JAGE::Input::KeyCode::F1
        #define JAGE_KEY_F2     JAGE::Input::KeyCode::F2
        #define JAGE_KEY_F3     JAGE::Input::KeyCode::F3
        #define JAGE_KEY_F4     JAGE::Input::KeyCode::F4
        #define JAGE_KEY_F5     JAGE::Input::KeyCode::F5
        #define JAGE_KEY_F6     JAGE::Input::KeyCode::F6
        #define JAGE_KEY_F7     JAGE::Input::KeyCode::F7
        #define JAGE_KEY_F8     JAGE::Input::KeyCode::F8
        #define JAGE_KEY_F9     JAGE::Input::KeyCode::F9
        #define JAGE_KEY_F10    JAGE::Input::KeyCode::F10
        #define JAGE_KEY_F11    JAGE::Input::KeyCode::F11
        #define JAGE_KEY_F12    JAGE::Input::KeyCode::F12

        #define JAGE_KEY_KP1 JAGE::Input::KeyCode::KP1
        #define JAGE_KEY_KP2 JAGE::Input::KeyCode::KP2
        #define JAGE_KEY_KP3 JAGE::Input::KeyCode::KP3
        #define JAGE_KEY_KP4 JAGE::Input::KeyCode::KP4
        #define JAGE_KEY_KP5 JAGE::Input::KeyCode::KP5
        #define JAGE_KEY_KP6 JAGE::Input::KeyCode::KP6
        #define JAGE_KEY_KP7 JAGE::Input::KeyCode::KP7
        #define JAGE_KEY_KP8 JAGE::Input::KeyCode::KP8
        #define JAGE_KEY_KP9 JAGE::Input::KeyCode::KP9
        #define JAGE_KEY_KP0 JAGE::Input::KeyCode::KP0

        #define JAGE_MOUSE_BUTTON_1             JAGE::Input::MouseButton::_1
        #define JAGE_MOUSE_BUTTON_2             JAGE::Input::MouseButton::_2
        #define JAGE_MOUSE_BUTTON_3             JAGE::Input::MouseButton::_3
        #define JAGE_MOUSE_BUTTON_4             JAGE::Input::MouseButton::_4
        #define JAGE_MOUSE_BUTTON_5             JAGE::Input::MouseButton::_5
        #define JAGE_MOUSE_BUTTON_LEFT_CLICK    JAGE_MOUSE_BUTTON_1
        #define JAGE_MOUSE_BUTTON_RIGHT_CLICK   JAGE_MOUSE_BUTTON_2
        #define JAGE_MOUSE_BUTTON_MIDDLE_CLICK  JAGE_MOUSE_BUTTON_3

        #define JAGE_ACTION_PRESSED     JAGE::Input::Action::PRESSED
        #define JAGE_ACTION_RELEASED    JAGE::Input::Action::RELEASED
        #define JAGE_ACTION_REPEATED    JAGE::Input::Action::REPEATED

        #define JAGE_MOD_NONE       JAGE::Input::Modifier::NONE
        #define JAGE_MOD_SHIFT      JAGE::Input::Modifier::SHIFT
        #define JAGE_MOD_CONTROL    JAGE::Input::Modifier::CONTROL
        #define JAGE_MOD_ALT        JAGE::Input::Modifier::ALT

        #define JAGE_CURSOR_MODE_NORMAL     JAGE::Input::CursorMode::NORMAL
        #define JAGE_CURSOR_MODE_DISABLED   JAGE::Input::CursorMode::DISABLED
        #define JAGE_CURSOR_MODE_HIDDEN     JAGE::Input::CursorMode::HIDDEN
    };
}

/**
 * 
 * 
 * LOGICAL PATH DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    /**
     * @class LogicalPath
     * 
     * @brief The `LogicalPath` class that represents any kind of path.
     * 
     * This class does not necessarily represent a file system path. Useful for DSLs, node graphs, config key
     * hierarchies, or any segment-based addressing scheme.
     */
    class LogicalPath
    {
    public:
        explicit LogicalPath(char delimiter = '/');
        explicit LogicalPath(std::string_view raw, char delimiter = '/');

        bool empty() const;
        std::size_t depth() const;

        const std::vector<std::string>& parts() const;
        LogicalPath parent() const;
        std::string_view stem() const;

        LogicalPath& push(std::string_view segment);
        std::string pop();
        LogicalPath& append(const LogicalPath& other);

        std::string string() const;

        bool operator==(const LogicalPath& other) const;
        bool operator!=(const LogicalPath& other) const;
    private:
        char m_delimiter;
        std::vector<std::string> m_segments;

        void parse(std::string_view raw);
        bool validate_segment(std::string_view segment) const;
    };

    LogicalPath operator/(LogicalPath lhs, std::string_view rhs);
    LogicalPath operator/(LogicalPath lhs, const LogicalPath& rhs);
    std::ostream& operator<<(std::ostream& os, const LogicalPath& path);

    std::filesystem::path operator/(std::filesystem::path lhs, LogicalPath rhs);
}

/**
 * 
 * 
 * URI DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    namespace URI { enum class Scheme : u8 { UNDEFINED = 0, FILE, GPU }; }

    namespace Data
    {
        struct URI
        {
            JAGE::URI::Scheme       scheme      {};
            std::string             userinfo    {};
            std::string             host        {};
            std::optional<u16>      port        {};
            LogicalPath             path        {};
            std::string             query       {};
            std::string             fragment    {};

            std::unordered_map<std::string, std::string> query_params {};

            bool has_authority() const { return !host.empty(); }
            bool is_valid() const { return scheme != JAGE::URI::Scheme::UNDEFINED; }

            std::string string() const;
        };
    }

    namespace URI
    {
        class ParseError final : public std::runtime_error
        {
        public:
            explicit ParseError(const std::string& msg);
        };

        std::string percent_encode(const std::string &input, std::string_view safe_chars = "");
        std::string percent_decode(const std::string &input);

        class Parser
        {
        public:
            static Data::URI parse(const std::string& raw);
        private:
            static bool is_valid_scheme_char(char c, bool first);
            static bool is_valid_host_char(char c);
            static Scheme               extract_scheme      (const std::string& raw, std::size_t &pos);
            static void                 extract_authority   (const std::string& raw, std::size_t &pos, Data::URI &out);
            static LogicalPath          extract_path        (const std::string& raw, std::size_t &pos);
            static std::string          extract_query       (const std::string& raw, std::size_t &pos);
            static std::string          extract_fragment    (const std::string& raw, std::size_t &pos);
            static std::unordered_map<std::string, std::string> parse_query_params(const std::string &query);
        };

        class Builder
        {
        public:
            Builder(Scheme scheme) : data {} { data.scheme = scheme; }

            Builder& userinfo   (std::string_view u)    { data.userinfo     = u; return *this; }
            Builder& host       (std::string_view h)    { data.host         = h; return *this; }
            Builder& port       (u16 p)                 { data.port         = p; return *this; }
            Builder& path       (LogicalPath p)         { data.path         = p; return *this; }
            Builder& query      (std::string_view q)    { data.query        = q; return *this; }
            Builder& fragment   (std::string_view f)    { data.fragment     = f; return *this; }

            Builder& add_query_param(const std::string& key, const std::string& value);

            Data::URI build() const { return data; }
            std::string to_string() const { return data.string(); }

        private:
            Data::URI data;
        };

        Data::URI undefined();
    }
}

/**
 * 
 * 
 * CORE EVENT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    enum class EventType : u8
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        Key, Char,
        MouseButton, MouseEnter, MouseMoved, MouseScrolled
    };

    enum class EventCategory : u8
    {
        None = 0,
        Application     = 1 << 0,
        Input           = 1 << 1,
        Keyboard        = 1 << 2,
        Mouse           = 1 << 3,
        MouseButton     = 1 << 4
    };

    JAGE_API int operator&(EventCategory lhs, EventCategory rhs);
    JAGE_API int operator|(EventCategory lhs, EventCategory rhs);

    /**
     * @class Event
     * @brief The `Event` base class used to communicate events happening between the JAGE and the application.
     */
    class JAGE_API Event
    {
    public:
        virtual std::string_view name() const = 0;
        virtual EventType event_type() const = 0;
        virtual int event_category_flags() const = 0;
        virtual std::string string() const;

        bool is_category(EventCategory category) const { return event_category_flags() & static_cast<int>(category); }

        bool handled() const { return m_handled; }
        void set_handled(bool handled) const { m_handled = handled; }
    protected:
        mutable bool m_handled {};
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.string(); }

    /**
     * @class EventDispatcher
     * @brief The `EventDispatcher` class used to dispatch events based on their event type.
     */
    class JAGE_API EventDispatcher
    {
        template<typename TEvent>
        using EventFn = std::function<bool(const TEvent&)>;
    public:
        EventDispatcher(const Event& event) : event { event } {}

        template<typename TEvent>
        void dispatch(EventFn<TEvent> function)
        {
            if (event.event_type() == TEvent::static_type())
            event.set_handled(function(static_cast<const TEvent&>(event)));
        }
    private:
        const Event& event;
    };
}

/**
 * 
 * 
 * MACRO FOR EVENTS DEFINITIONS
 * 
 * 
 */

/**
 * @def EVENT_CLASS_TYPE
 * @brief A macro to override virtual functions from `Event` at derived classes.
 *
 * The EVENT_CLASS_TYPE macro will expand to override virtual functions from `Event` at classes that derive `Event`.
 * It also includes expanding the static function `static_type()` which returns the event type for the event class it
 * is in.
 */
#define EVENT_CLASS_TYPE(TYPE) \
    static EventType static_type() { return EventType::TYPE; } \
    virtual EventType event_type() const override { return static_type(); } \
    virtual std::string_view name() const override { return #TYPE; }

#define EVENT_CLASS_CATEGORY(CATEGORY) \
    virtual int event_category_flags() const override { return static_cast<int>(CATEGORY); }

/**
 * 
 * 
 * APPLICATION/WINDOW EVENT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    class JAGE_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API WindowResizeEvent : public Event
    {
    private:
        const unsigned m_width;
        const unsigned m_height;
    public:
        WindowResizeEvent(unsigned width, unsigned height) : m_width { width }, m_height { height } {}

        unsigned width() const { return m_width; }
        unsigned height() const { return m_height; }

        std::string string() const override;

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API WindowFocusEvent : public Event
    {
    private:
        const bool m_focused;
    public:
        WindowFocusEvent(bool focused) : m_focused { focused } {}

        bool focused() const { return m_focused; }

        std::string string() const override;

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };
}

/**
 * 
 * 
 * KEY/CHAR EVENT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    class JAGE_API KeyEvent : public Event
    {
    public:
        KeyEvent(Input::KeyCode key, int scancode, Input::Action action, int mods)
        : m_key { key }
        , m_scancode { scancode }
        , m_action { action }
        , m_mods { mods }
        {}

        Input::KeyCode  key()       const { return m_key; }
        int             scancode()  const { return m_scancode; }
        Input::Action   action()    const { return m_action; }
        int             mods()      const { return m_mods; }

        std::string string() const override;

        EVENT_CLASS_TYPE(Key)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
    private:
        const Input::KeyCode    m_key;
        const int               m_scancode;
        const Input::Action     m_action;
        const int               m_mods;
    };

    class JAGE_API CharEvent : public Event
    {
    public:
        CharEvent(unsigned codepoint) : m_codepoint { codepoint } {}

        unsigned codepoint() const { return m_codepoint; }

        std::string string() const override;

        EVENT_CLASS_TYPE(Char)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
    private:
        const unsigned m_codepoint;
    };
}

/**
 * 
 * 
 * MOUSE EVENT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    class JAGE_API MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(Input::MouseButton button, Input::Action action, int mods)
        : m_button { button }
        , m_action { action }
        , m_mods { mods }
        {}

        Input::MouseButton  button()    const { return m_button; }
        Input::Action       action()    const { return m_action; }
        int                 mods()      const { return m_mods; }

        std::string string() const override;

        EVENT_CLASS_TYPE(MouseButton)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const Input::MouseButton    m_button;
        const Input::Action         m_action;
        const int                   m_mods;
    };

    class JAGE_API MouseEnterEvent : public Event
    {
    public:
        MouseEnterEvent(int entered) : m_entered { entered } {}

        int entered() const { return m_entered; }

        std::string string() const override;

        EVENT_CLASS_TYPE(MouseEnter)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const int m_entered;
    };

    class JAGE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float mouseX, float mouseY) : m_mouseX { mouseX }, m_mouseY { mouseY } {}

        float mouseX() const { return m_mouseX; }
        float mouseY() const { return m_mouseY; }

        std::string string() const override;

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_mouseX;
        const float m_mouseY;
    };

    class JAGE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float offsetX, float offsetY) : m_offsetX { offsetX }, m_offsetY { offsetY } {}

        float offsetX() const { return m_offsetX; }
        float offsetY() const { return m_offsetY; }

        std::string string() const override;

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_offsetX;
        const float m_offsetY;
    };
}
