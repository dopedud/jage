#pragma once

#include "jgpch.h"

#include "api_export.h"

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

    /**
     * @def EVENT_CLASS_TYPE macro
     * @brief A macro to override virtual functions from @c Event at derived classes.
     *
     * The EVENT_CLASS_TYPE macro will expand to override virtual functions from @c Event at classes that derive @c
     * Event. It also includes expanding the static function @c static_type() which returns the event type for the
     * event class it is in.
     */
    #define EVENT_CLASS_TYPE(type)\
        static EventType static_type() { return EventType::##type; }\
        virtual EventType event_type() const override { return static_type(); }\
        virtual std::string_view name() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category)\
        virtual int event_category_flags() const override { return static_cast<int>(category); }

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool{ T& }>;
    public:
        EventDispatcher(Event& event) : m_event { event } {}

        template<typename T>
        bool Dispatch(EventFn<T> function)
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

namespace JAGE
{
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}
