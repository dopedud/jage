#pragma once

/**
 * @file core.h
 * @brief The Core header file that contains the core subsystems and utilities for JAGE.
 */

#include "jgpch.h"

#include "api_export.h"

/**
 * MACRO DEFINITIONS
 */

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
#if defined(MSC_VER)
#   define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#   if defined(__has_builtin)
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
 * MACRO FOR LOGGING DEFINITIONS
 */
#define JAGE_MSG_TRACE(MSG) JAGE::Logger::EngineLog_Trace(MSG)
#define JAGE_MSG_DEBUG(MSG) JAGE::Logger::EngineLog_Debug(MSG)
#define JAGE_MSG_INFO(MSG) JAGE::Logger::EngineLog_Info(MSG)
#define JAGE_MSG_WARN(MSG) JAGE::Logger::EngineLog_Warn(MSG)
#define JAGE_MSG_ERROR(MSG) JAGE::Logger::EngineLog_Error(MSG)

#define APP_MSG_TRACE(MSG) JAGE::Logger::AppLog_Trace(MSG)
#define APP_MSG_DEBUG(MSG) JAGE::Logger::AppLog_Debug(MSG)
#define APP_MSG_INFO(MSG) JAGE::Logger::AppLog_Info(MSG)
#define APP_MSG_WARN(MSG) JAGE::Logger::AppLog_Warn(MSG)
#define APP_MSG_ERROR(MSG) JAGE::Logger::AppLog_Error(MSG)

#define JAGE_LOG_TRACE(LOG, ...) JAGE::Logger::EngineLog_Trace(LOG, __VA_ARGS__)
#define JAGE_LOG_DEBUG(LOG, ...) JAGE::Logger::EngineLog_Debug(LOG, __VA_ARGS__)
#define JAGE_LOG_INFO(LOG, ...) JAGE::Logger::EngineLog_Info(LOG, __VA_ARGS__)
#define JAGE_LOG_WARN(LOG, ...) JAGE::Logger::EngineLog_Warn(LOG, __VA_ARGS__)
#define JAGE_LOG_ERROR(LOG, ...) JAGE::Logger::EngineLog_Error(LOG, __VA_ARGS__)

#define APP_LOG_TRACE(LOG, ...) JAGE::Logger::AppLog_Trace(LOG, __VA_ARGS__)
#define APP_LOG_DEBUG(LOG, ...) JAGE::Logger::AppLog_Debug(LOG, __VA_ARGS__)
#define APP_LOG_INFO(LOG, ...) JAGE::Logger::AppLog_Info(LOG, __VA_ARGS__)
#define APP_LOG_WARN(LOG, ...) JAGE::Logger::AppLog_Warn(LOG, __VA_ARGS__)
#define APP_LOG_ERROR(LOG, ...) JAGE::Logger::AppLog_Error(LOG, __VA_ARGS__)
/**
 * END MACRO FOR LOGGING DEFINITIONS
 */

/**
 * MACRO FOR ASSERTIONS DEFINITIONS
 */
#ifdef JAGE_ENABLE_ASSERTS
#   define JAGE_CORE_ASSERT(x, ...) \
    if (!(x)) { JAGE_LOG_ERROR("Assertion failed: {}", __VA_ARGS__); }
#   define JAGE_CORE_ASSERT_CALLBACK(x, callback, ...) \
    if (!(x)) { JAGE_LOG_ERROR("Assertion failed: {}", __VA_ARGS__); callback; }
#else
#   define JAGE_CORE_ASSERT(x, ...)
#   define JAGE_CORE_ASSERT_CALLBACK(x, callback, ...)
#endif
/**
 * END MACRO FOR ASSERTIONS DEFINITIONS
 */

/**
 * MACRO FOR EVENTS DEFINITIONS
 */

/**
 * @def EVENT_CLASS_TYPE macro
 * @brief A macro to override virtual functions from @c Event at derived classes.
 *
 * The EVENT_CLASS_TYPE macro will expand to override virtual functions from @c Event at classes that derive @c
 * Event. It also includes expanding the static function @c static_type() which returns the event type for the
 * event class it is in.
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

/**
 * LOGGER DEFINITIONS
 */

#include "spdlog/spdlog.h"

namespace JAGE
{
    /**
     * @class Logger
     * @brief The Logger class used for logging JAGE and the game.
     * 
     * This Logger class uses @c spdlog as its logging backend. However, it is exposed to the end-user (i.e. the game),
     * effectively making JAGE and the game depend on @c spdlog to log. This tightly-coupled dependency should pose no
     * issues since logging rarely requires the developer to switch between different backends (compared to something
     * like a physics engine where a developer might use different ones for different scenarios).
     * 
     * The reason for the tightly-coupled dependency is because @c spdlog uses variadic templates internally to enable
     * variable number and types of objects to log. By defnition, templates should have its implementation exposed, so
     * both JAGE and the game should know what @c spdlog is.
     * 
     * It is possible to have only the JAGE know what logging backend it's using, and let the game use logging
     * from the JAGE without knowing what's going on internally by using the @c PImpl (pointer-to-implementation)
     * pattern. However, some sacrifices need to be made for templates and the @c PImpl pattern to work together.
     * Templates must be explicitly instantiated in the translation unit for types that a developer wants to support.
     * However, doing this would defeat the whole purpose of templates, which is to allow the flexibility of supporting
     * any type and any number of them. In fact, it is better to just overload the same function with different types
     * and amount of arguments a developer wants to support, since the intent is clearer.
     * 
     * Templates and the @c PImpl pattern are programming patterns that go against each other. Templates require the
     * implementation to be exposed, while the @c PImpl pattern requires it to be hidden. Templates are chose over the
     * @c PImpl pattern since the flexibility that comes with it is more important.
     */
    class JAGE_API Logger
    {
    private:
        inline static std::shared_ptr<spdlog::logger> enginelog = nullptr;
        inline static std::shared_ptr<spdlog::logger> applog = nullptr;
    public:
        static void Init(spdlog::level::level_enum engine_level, spdlog::level::level_enum app_level);

        inline static void EngineLog_Trace(std::string_view msg) { enginelog->trace(msg); }
        inline static void EngineLog_Debug(std::string_view msg) { enginelog->debug(msg); }
        inline static void EngineLog_Info(std::string_view msg) { enginelog->info(msg); }
        inline static void EngineLog_Warn(std::string_view msg) { enginelog->warn(msg); }
        inline static void EngineLog_Error(std::string_view msg) { enginelog->error(msg); }

        inline static void AppLog_Trace(std::string_view msg) { applog->trace(msg); }
        inline static void AppLog_Debug(std::string_view msg) { applog->debug(msg); }
        inline static void AppLog_Info(std::string_view msg) { applog->info(msg); }
        inline static void AppLog_Warn(std::string_view msg) { applog->warn(msg); }
        inline static void AppLog_Error(std::string_view msg) { applog->error(msg); }

        template<typename... Args>
        inline static void EngineLog_Trace(std::string_view log, Args &&... args)
        { enginelog->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Debug(std::string_view log, Args &&... args)
        { enginelog->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Info(std::string_view log, Args &&... args)
        { enginelog->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Warn(std::string_view log, Args &&... args)
        { enginelog->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Error(std::string_view log, Args &&... args)
        { enginelog->error(log, std::forward<Args>(args)...); }

        template<typename... Args>
        inline static void AppLog_Trace(std::string_view log, Args &&... args)
        { applog->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Debug(std::string_view log, Args &&... args)
        { applog->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Info(std::string_view log, Args &&... args)
        { applog->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Warn(std::string_view log, Args &&... args)
        { applog->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Error(std::string_view log, Args &&... args)
        { applog->error(log, std::forward<Args>(args)...); }
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

    #define BIT(x) (1 << x)

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
        int lhs_casted = static_cast<int>(lhs);
        int rhs_casted = static_cast<int>(rhs);
        return lhs_casted & rhs_casted;
    }

    inline int operator|(EventCategory lhs, EventCategory rhs)
    {
        int lhs_casted = static_cast<int>(lhs);
        int rhs_casted = static_cast<int>(rhs);
        return lhs_casted | rhs_casted;
    }

    class JAGE_API Event
    {
    public:
        virtual std::string_view name() const = 0;
        virtual EventType event_type() const = 0;
        virtual int event_category_flags() const = 0;
        virtual std::string_view ToString() const { return std::string{ name() } + "Event"; }

        inline bool is_category(EventCategory category) { return event_category_flags() & static_cast<int>(category); }
    protected:
        bool handled = false;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : m_event { event } {}

        template<typename T>
        inline bool dispatch(EventFn<T> function)
        {
            if (m_event.event_type() == T::static_type())
            {
                m_event.handled = function(*(T*)&m_event);
                return true;
            }

            return false;
        }
    private:
        Event& m_event;
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
        unsigned int m_width, m_height;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width { width }
        , m_height { height }
        {}

        inline unsigned int width() const { return m_width; }
        inline unsigned int height() const { return m_height; }

        std::string_view ToString() const override
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
    protected:
        int m_keycode {};
        
        KeyEvent(int keycode) : m_keycode { keycode } {}
    public:
        inline int keycode() const { return m_keycode; }

        EVENT_CLASS_CATEGORY(EventCategory::Keyboard | EventCategory::Input)
    };

    class JAGE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeat_count)
        : KeyEvent { keycode }
        , m_repeat_count { repeat_count }
        {}

        inline int repeat_count() const { return m_repeat_count; }

        std::string_view ToString() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_keycode << " (" << m_repeat_count << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_repeat_count;
    };

    class JAGE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent { keycode } {}

        std::string_view ToString() const override
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
    private:
        float m_mouseX, m_mouseY;
    public:
        MouseMovedEvent(float x, float y)
        : m_mouseX { x }
        , m_mouseY { y }
        {}

        inline float x() const { return m_mouseX; }
        inline float y() const { return m_mouseY; }
        
        std::string_view ToString() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    };

    class JAGE_API MouseScrolledEvent : public Event
    {
    private:
        float m_offsetX, m_offsetY;
    public:
        MouseScrolledEvent(float offsetX, float offsetY)
        : m_offsetX { offsetX }
        , m_offsetY { offsetY }
        {}

        inline float offsetX() const { return m_offsetX; }
        inline float offsetY() const { return m_offsetY; }
        
        std::string_view ToString() const override
        {
            std::stringstream ss;
            ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    };

    class JAGE_API MouseButtonEvent : public Event
    {
    public:
        inline int mouse_button() { return m_mouse_button; }

        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    protected:
        int m_mouse_button;

        MouseButtonEvent(int mouse_button) : m_mouse_button { mouse_button } {}
    };

    class JAGE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int mouse_button) : MouseButtonEvent{ mouse_button } {}

        std::string_view ToString() const override
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

        std::string_view ToString() const override
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
    struct WindowProperties
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProperties(
            const std::string& title = "JAGE Engine",
            unsigned int width = 1280,
            unsigned int height = 720
        )
        : title { title }
        , width { width }
        , height { height }
        {}
    };        

    class JAGE_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int width() const = 0;
        virtual unsigned int height() const = 0;

        virtual void set_eventcallback(const EventCallbackFn& callback) = 0;
        virtual void set_vsync(bool enabled) = 0;
        virtual bool is_vsync() const = 0;

        static Window* create(const WindowProperties& properties = WindowProperties());
    };
}
/**
 * END WINDOW DEFINITIONS
 */
