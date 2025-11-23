#pragma once

/**
 * @file core.h
 * @brief The Core header file that contains the core subsystems and utilities for JAGE.
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
 * - INITIALIZATION/DESTRUCTION DEFINITIONS
 * - TIMING DEFINITIONS
 * - LOGGER DEFINITIONS
 * - WINDOW DEFINITIONS
 * - LAYER DEFINITIONS
 * - GRAPHICS CONTEXT DEFINITIONS
 * - INPUT DEFINITIONS
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
#elif defined(__GNUC__) && __GNUC__ >= 4
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
 * MACRO FOR SHIFT-LEFT BIT OPERATION
 * 
 * 
 */
#define BIT(x) (1 << x)

/**
 * 
 * 
 * INITIALIZATION/DESTRUCTION DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    void JAGE_API Init(int argc, char** argv);
    void JAGE_API Destroy();
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
        void JAGE_API StartLoop();
        void JAGE_API EndLoop();
        double JAGE_API ElapsedTime();
        double JAGE_API DeltaTime();
        void JAGE_API WaitForFPS();
    }
}

/**
 * 
 * 
 * LOGGER DEFINITIONS
 * 
 * 
 */
#include "spdlog/spdlog.h"

namespace JAGE
{
    /**
     * @class AppLogger
     * @brief The AppLogger class used to log game operations.
     *
     * Both JAGE and the game use @c spdlog as its logging backend. This means that the game won't really rely on JAGE
     * to provide logging utilities, but instead rely directly from @c spdlog . Ideally, the opposite should happen
     * (the game relying on JAGE and not having to fuss around with the implementation/backend), though for the case of
     * logging, there's really no reason to switch between different backends as long as it works as intended. 
     *
     * The reason for this tightly-coupled dependency is because @c spdlog uses variadic templates internally to enable
     * variable number and types of objects to log. By defnition, templates should have its implementation exposed. As
     * a consequence, both JAGE and the game should know what @c spdlog is.
     *
     * It is possible to have only JAGE know what logging backend it's using, and let the game use logging from JAGE
     * without knowing what's going on internally by using the @c PImpl (pointer-to-implementation) pattern. However,
     * some sacrifices had to be made for templates and the @c PImpl pattern to work together. Templates must be
     * explicitly instantiated in translation units for types one wants to support. However, doing this would defeat
     * the whole purpose of templates, which is to allow the flexibility of supporting any type and any number of them.
     * In fact, it is better to just overload the same function with different types and different amount of arguments
     * one wants to support, since the intent is clearer.
     *
     * Templates and the @c PImpl pattern are programming patterns that go against each other. Templates require the
     * implementation to be exposed, while the @c PImpl pattern requires it to be hidden. Templates are chose over the
     * @c PImpl pattern since the flexibility that comes with it is more important.
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
 * WINDOW DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    // forward declare Event class to be used by Layer class and Window class
    class JAGE_API Event;

    // forward declare GraphicsContext class and Layer class to be used by Window class
    class JAGE_API GraphicsContext;
    class JAGE_API Layer;

    struct JAGE_API WindowProperties
    {
        std::string title;
        unsigned width;
        unsigned height;
        bool vsync;

        WindowProperties(
            std::string_view title = "JAGE Engine",
            unsigned width = 1280,
            unsigned height = 720,
            bool vsync = false
        )
        : title { title }
        , width { width }
        , height { height }
        , vsync { vsync }
        {}
    };

    using EventCallbackFn = std::function<void(const Event&)>;

    class JAGE_API Window
    {
    public:
        static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties{});
        virtual ~Window() = default;

        unsigned width() const { return data.properties.width; }
        unsigned height() const { return data.properties.height; }

        virtual void OnRender() = 0;

        void set_eventcallback(const EventCallbackFn& callback) { data.callback = callback; }

        bool vsync() const { return data.properties.vsync; }
        virtual void set_vsync(bool enabled) = 0;

        /**
         * @fn handle()
         * @brief A function to expose backend implementation of a window.
         * 
         * This should be used only if you know what you're doing.
         */
        virtual void* handle() = 0;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        void OnEvent(const Event& e);

        // for use in for loops and search algorithms like std::find
        std::vector<Layer*>::iterator layers_begin() { return layers.begin(); }
        std::vector<Layer*>::iterator layers_end() { return layers.end(); }
    protected:
        std::unique_ptr<GraphicsContext> graphics_context;

        std::vector<Layer*> layers {};
        int layer_insert_index {};

        struct WindowData
        {
            WindowProperties properties;
            EventCallbackFn callback;
            EventCallbackFn OnEvent;
        };

        WindowData data;
    };
}

/**
 * 
 * 
 * LAYER DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    class JAGE_API Layer
    {
    public:
        Layer(Window* window, std::string_view name = "Unnamed Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;

        virtual void OnRender() = 0;

        virtual void OnEvent(const Event& e) = 0;

        std::string name() const { return m_name; }
    protected:
        Window* window;
        const std::string m_name;
    };
}

/**
 * 
 * 
 * GRAPHICS CONTEXT DEFINITIONS
 * 
 * 
 */
namespace JAGE
{
    class JAGE_API GraphicsContext
    {
    public:
        GraphicsContext(Window* window) : window { window } {}

        virtual void Clear() = 0;
        virtual void SwapBuffers() = 0;
    protected:
        Window* window;
    };
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
        enum class KeyCode : uint16_t
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

        enum class MouseButton : uint8_t
        {
            _1 = 0, _2, _3, _4, _5
        };

        enum class Action : uint8_t
        {
            PRESSED = 0, RELEASED, REPEATED
        };

        enum class Modifier : uint8_t
        {
            NONE        = 0,
            SHIFT       = BIT(0),
            CONTROL     = BIT(1),
            ALT         = BIT(2),
        };

        int JAGE_API operator&(Modifier lhs, Modifier rhs);
        int JAGE_API operator|(Modifier lhs, Modifier rhs);
        int JAGE_API operator&(int lhs, Modifier rhs);
        int JAGE_API operator|(int lhs, Modifier rhs);
        int JAGE_API operator&(Modifier lhs, int rhs);
        int JAGE_API operator|(Modifier lhs, int rhs);

        /**
         * @fn SetActiveWindow
         * @brief Sets the active window to query input from.
         * 
         * Querying input should only be for a single window at any given moment in time.
         * 
         * @param window The window to query input from. 
         */
        void JAGE_API SetActiveWindow(Window* window);

        bool JAGE_API IsKeyPressed(KeyCode key);
        bool JAGE_API IsMouseButtonPressed(MouseButton button);

        std::pair<float, float> JAGE_API GetMousePosition();
        float JAGE_API GetMousePositionX();
        float JAGE_API GetMousePositionY();

        std::string JAGE_API to_string(KeyCode key);
        std::string JAGE_API to_string(Action action);
        std::string JAGE_API to_string(MouseButton button);
        std::string JAGE_API to_string(int mods);

        std::ostream& JAGE_API operator<<(std::ostream& os, const KeyCode& key);
        std::ostream& JAGE_API operator<<(std::ostream& os, const Action& action);
        std::ostream& JAGE_API operator<<(std::ostream& os, const MouseButton& button);
        std::ostream& JAGE_API operator<<(std::ostream& os, const int& mods);

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
    };
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
    /**
     * NOTE: @c int is used as the underlying type for @c EventType and @c EventCategory
     */

    enum class EventType : uint8_t
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        Key, Char,
        MouseButton, MouseEnter, MouseMoved, MouseScrolled
    };

    enum class EventCategory : uint8_t
    {
        None = 0,
        Application     = BIT(0),
        Input           = BIT(1),
        Keyboard        = BIT(2),
        Mouse           = BIT(3),
        MouseButton     = BIT(4)
    };

    int JAGE_API operator&(EventCategory lhs, EventCategory rhs);
    int JAGE_API operator|(EventCategory lhs, EventCategory rhs);

    /**
     * @class Event
     * @brief The @c Event base class used to communicate events happening between the engine and the application.
     */
    class JAGE_API Event
    {
    public:
        virtual std::string name() const = 0;
        virtual EventType event_type() const = 0;
        virtual int event_category_flags() const = 0;
        virtual std::string to_string() const { return name() + "Event"; }

        bool category(EventCategory category) const { return event_category_flags() & static_cast<int>(category); }

        bool handled() const { return m_handled; }
        void set_handled(bool handled) const { m_handled = handled; }
    protected:
        mutable bool m_handled {};
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.to_string(); }

    /**
     * @class EventDispatcher
     * @brief The @c EventDispatcher class used to dispatch events based on their event type.
     */
    class JAGE_API EventDispatcher
    {
        template<typename TEvent>
        using EventFn = std::function<bool(const TEvent&)>;
    public:
        EventDispatcher(const Event& event) : event { event } {}

        template<typename TEvent>
        bool dispatch(EventFn<TEvent> function)
        {
            if (event.event_type() == TEvent::static_type())
            {
                event.set_handled(function(static_cast<const TEvent&>(event)));
                return true;
            }

            return false;
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
 * @brief A macro to override virtual functions from @c Event at derived classes.
 *
 * The EVENT_CLASS_TYPE macro will expand to override virtual functions from @c Event at classes that derive @c Event.
 * It also includes expanding the static function @c static_type() which returns the event type for the event class it
 * is in.
 */
#define EVENT_CLASS_TYPE(type) \
    static EventType static_type() { return EventType::type; } \
    virtual EventType event_type() const override { return static_type(); } \
    virtual std::string name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int event_category_flags() const override { return static_cast<int>(category); }

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

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

        std::string to_string() const override;

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_offsetX;
        const float m_offsetY;
    };
}
