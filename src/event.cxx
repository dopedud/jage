#include "JAGE/core.h"

namespace JAGE
{
    int operator&(EventCategory lhs, EventCategory rhs)
    {
        int lhs_casted { static_cast<int>(lhs) };
        int rhs_casted { static_cast<int>(rhs) };
        return lhs_casted & rhs_casted;
    }

    int operator|(EventCategory lhs, EventCategory rhs)
    {
        int lhs_casted { static_cast<int>(lhs) };
        int rhs_casted { static_cast<int>(rhs) };
        return lhs_casted | rhs_casted;
    }

    std::string_view Event::to_string() const
    {
        m_to_string = std::string{ name() } + "Event";
        return m_to_string;
    }

    std::string_view WindowResizeEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_width << ", " << m_height;
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view WindowFocusEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << (m_focused ? "window focused." : "window unfocused.");
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view KeyEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_key << ", " << m_scancode << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view CharEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_codepoint;
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view MouseButtonEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_button << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view MouseEnterEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << (m_entered ? "mouse entered." : "mouse exited.");
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view MouseMovedEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
        m_to_string = ss.str();
        return m_to_string;
    }

    std::string_view MouseScrolledEvent::to_string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
        m_to_string = ss.str();
        return m_to_string;
    }
}
