#pragma once

/**
 * @file core.h
 * @brief The Core header file that contains the core subsystems and utilities for JAGE.
 */

#include "jgpch.h"

/**
 * MACRO DEFINITIONS
 */

/**
 * MACRO FOR API EXPORT DEFINITIONS
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
 * END MACRO FOR API EXPORT DEFINITIONS
 */

/**
 * MACRO FOR SUPPRESSING WARNINGS IN CODE
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
 * END MACRO FOR SUPPRESSING WARNINGS IN CODE
 */

/**
 * MACRO FOR LOGGING DEFINITIONS
 */
#define APP_MSG_TRACE(MSG) JAGE::AppLogger::Trace(MSG)
#define APP_MSG_DEBUG(MSG) JAGE::AppLogger::Debug(MSG)
#define APP_MSG_INFO(MSG) JAGE::AppLogger::Info(MSG)
#define APP_MSG_WARN(MSG) JAGE::AppLogger::Warn(MSG)
#define APP_MSG_ERROR(MSG) JAGE::AppLogger::Error(MSG)

#define APP_LOG_TRACE(LOG, ...) JAGE::AppLogger::Trace(LOG, __VA_ARGS__)
#define APP_LOG_DEBUG(LOG, ...) JAGE::AppLogger::Debug(LOG, __VA_ARGS__)
#define APP_LOG_INFO(LOG, ...) JAGE::AppLogger::Info(LOG, __VA_ARGS__)
#define APP_LOG_WARN(LOG, ...) JAGE::AppLogger::Warn(LOG, __VA_ARGS__)
#define APP_LOG_ERROR(LOG, ...) JAGE::AppLogger::Error(LOG, __VA_ARGS__)
/**
 * END MACRO FOR LOGGING DEFINITIONS
 */

#define BIT(x) (1 << x)

/**
 * MACRO FOR BREAKPOINT INSTRUCTIONS DEFINITIONS
 */

/**
 * @define DEBUG_BREAK() macro
 * @brief A macro to set breakpoint inside the code itself.
 *
 * Setting breakpoints in code depends on the platform. Each platform has their own way of doing it, and this macro
 * helps to cover the cases for all platforms.
 */
#ifdef _MSC_VER
#   define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#   ifdef __has_builtin
#       if __has_builtin(__builtin_debugtrap)
#           define DEBUG_BREAK() __builtin_debugtrap()
#       else
#           define DEBUG_BREAK() __builtin_trap()
#       endif
#   else
#       define DEBUG_BREAK() raise(SIGTRAP)
#   endif
#else
#   include <csignal>
#   define DEBUG_BREAK() std::raise(SIGTRAP)
#endif

/**
 * END MACRO FOR BREAKPOINT INSTRUCTIONS DEFINITIONS
 */

/**
 * MACRO FOR EVENTS DEFINITIONS
 */

/**
 * @def EVENT_CLASS_TYPE macro
 * @brief A macro to override virtual functions from @c Event at derived classes.
 *
 * The EVENT_CLASS_TYPE macro will expand to override virtual functions from @c Event at classes that derive @c Event.
 * It also includes expanding the static function @c static_type() which returns the event type for the event class it
 * is in.
 */
#define EVENT_CLASS_TYPE(type) \
    inline static EventType static_type() { return EventType::type; } \
    virtual EventType event_type() const override { return static_type(); } \
    virtual std::string_view name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int event_category_flags() const override { return static_cast<int>(category); }

/**
 * END MACRO FOR EVENTS DEFINITIONS
 */

/**
 * END MACRO DEFINITIONS
 */

namespace JAGE
{
    void JAGE_API Init(int argc, char** argv);
}

/**
 * LOGGER DEFINITIONS
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

        inline static void Trace(std::string_view msg) { logger->trace(msg); }
        inline static void Debug(std::string_view msg) { logger->debug(msg); }
        inline static void Info(std::string_view msg) { logger->info(msg); }
        inline static void Warn(std::string_view msg) { logger->warn(msg); }
        inline static void Error(std::string_view msg) { logger->error(msg); }

        template<typename... Args>
        inline static void Trace(std::string_view log, Args &&... args)
        { logger->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Debug(std::string_view log, Args &&... args)
        { logger->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Info(std::string_view log, Args &&... args)
        { logger->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Warn(std::string_view log, Args &&... args)
        { logger->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Error(std::string_view log, Args &&... args)
        { logger->error(log, std::forward<Args>(args)...); }
    };
}
/**
 * END LOGGER DEFINITIONS
 */

/**
 * CORE EVENT DEFINITIONS
 */
namespace JAGE
{
    /**
     * NOTE: @c int is used as the underlying type for @c EventType and @c EventCategory
     */

    enum class EventType : int
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowUnFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };   

    enum class EventCategory : int
    {
        None = 0,
        Application     = BIT(0),
        Input           = BIT(1),
        Keyboard        = BIT(2),
        Mouse           = BIT(3),
        MouseButton     = BIT(4)
    };

    inline int operator&(EventCategory lhs, EventCategory rhs)
    {
        int lhs_casted { static_cast<int>(lhs) };
        int rhs_casted { static_cast<int>(rhs) };
        return lhs_casted & rhs_casted;
    }

    inline int operator|(EventCategory lhs, EventCategory rhs)
    {
        int lhs_casted { static_cast<int>(lhs) };
        int rhs_casted { static_cast<int>(rhs) };
        return lhs_casted | rhs_casted;
    }

    /**
     * @class Event
     * @brief The @c Event base class used to communicate events happening between the engine and the application.
     */
    class JAGE_API Event
    {
    public:
        virtual std::string_view name() const = 0;
        virtual EventType event_type() const = 0;
        virtual int event_category_flags() const = 0;
        virtual std::string_view to_string() const { return std::string{ name() } + "Event"; }

        bool category(EventCategory category) const { return event_category_flags() & static_cast<int>(category); }
        bool handled() const { return m_handled; }
        void set_handled(bool handled) const { this->m_handled = handled; }
    protected:
        mutable bool m_handled { false };
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.to_string();
    }

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(const T&)>;
    public:
        EventDispatcher(const Event& event) : event { event } {}

        template<typename T>
        bool dispatch(EventFn<T> function)
        {
            if (event.event_type() == T::static_type())
            {
                event.set_handled(function(static_cast<const T&>(event)));
                return true;
            }

            return false;
        }
    private:
        const Event& event;
    };
}
/**
 * END CORE EVENT DEFINITIONS
 */

/**
 * APPLICATION/WINDOW EVENT DEFINITIONS
 */
namespace JAGE
{
    class JAGE_API WindowResizeEvent : public Event
    {
    private:
        const unsigned int m_width, m_height;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_width { width }, m_height { height } {}

        unsigned int width() const { return m_width; }
        unsigned int height() const { return m_height; }

        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_width << ", " << m_height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API AppTickEvent : public Event
    {
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API AppUpdateEvent : public Event
    {
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class JAGE_API AppRenderEvent : public Event
    {
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };
}
/**
 * END APPLICATION/WINDOW EVENT DEFINITIONS
 */

/**
 * KEY EVENT DEFINITIONS
 */
namespace JAGE
{
    class JAGE_API KeyEvent : public Event
    {
    public:
        int keycode() const { return m_keycode; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
    protected:
        const int m_keycode {};
        
        KeyEvent(int keycode) : m_keycode { keycode } {}
    };

    class JAGE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, bool isrepeat) : KeyEvent { keycode }, m_isrepeat { isrepeat } {}

        bool is_repeat() const { return m_isrepeat; }

        std::string_view to_string() const override
        {
            std::stringstream ss;
            if (!m_isrepeat) ss << name() << "Event: " << m_keycode; 
            else ss << name() << "Event: " << m_keycode << " (repeating)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        const bool m_isrepeat;
    };

    class JAGE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent { keycode } {}

        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
/**
 * END KEY EVENT DEFINITIONS
 */

/**
 * MOUSE EVENT DEFINITIONS
 */
namespace JAGE
{
    class JAGE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float mouseX, float mouseY) : m_mouseX { mouseX }, m_mouseY { mouseY } {}

        float mouseX() const { return m_mouseX; }
        float mouseY() const { return m_mouseY; }
        
        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_mouseX, m_mouseY;
    };

    class JAGE_API MouseScrolledEvent : public Event
    {
    private:
        const float m_offsetX, m_offsetY;
    public:
        MouseScrolledEvent(float offsetX, float offsetY) : m_offsetX { offsetX }, m_offsetY { offsetY } {}

        float offsetX() const { return m_offsetX; }
        float offsetY() const { return m_offsetY; }
        
        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    };

    class JAGE_API MouseButtonEvent : public Event
    {
    public:
        int mouse_button() { return m_mouse_button; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    protected:
        const int m_mouse_button;

        MouseButtonEvent(int mouse_button) : m_mouse_button { mouse_button } {}
    };

    class JAGE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int mouse_button) : MouseButtonEvent{ mouse_button } {}

        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_mouse_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class JAGE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int mouse_button) : MouseButtonEvent { mouse_button } {}

        std::string_view to_string() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_mouse_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
/**
 * END MOUSE EVENT DEFINITIONS
 */

/**
 * WINDOW DEFINITIONS
 */
namespace JAGE
{
    using EventCallbackFn = std::function<void(const Event&)>;

    struct WindowProperties
    {
        std::string title;
        unsigned int width, height;
        bool vsync;

        WindowProperties(
            const std::string& title = "JAGE Engine",
            unsigned int width = 1280,
            unsigned int height = 720,
            bool vsync = false
        )
        : title { title }
        , width { width }
        , height { height }
        , vsync { vsync }
        {}
    };        

    class JAGE_API Window
    {
    public:
        Window(const WindowProperties& properties = WindowProperties{});
        ~Window();

        unsigned int width() const;
        unsigned int height() const;

        void OnUpdate();

        void set_eventcallback(const EventCallbackFn& callback);

        void set_vsync(bool enabled);
        bool vsync() const;

        void* handle();
    private:
        class Window_Impl;
        std::unique_ptr<Window_Impl> pImpl;
    };
}
/**
 * END WINDOW DEFINITIONS
 */

/**
 * LAYER AND LAYERSTACK DEFINITIONS
 */
namespace JAGE
{
    class JAGE_API Layer
    {
    public:
        Layer(std::string_view name = "Unnamed Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(const Event& e) = 0;
        
        inline std::string_view name() const { return m_name; }
    protected:
        std::string m_name;
    };

    class JAGE_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        void OnUpdate();
        void OnEvent(const Event& e);

        std::vector<Layer*>::iterator begin() { return layers.begin(); }
        std::vector<Layer*>::iterator end() { return layers.end(); }
    private:
        std::vector<Layer*> layers {};
        std::vector<Layer*>::iterator layer_insert;
    };
}
/**
 * END LAYER AND LAYERSTACK DEFINITIONS
 */
