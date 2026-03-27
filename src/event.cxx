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

    std::string Event::string() const { return std::string{ name() } + "Event"; }

    std::string WindowResizeEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_width << ", " << m_height;
        return ss.str();
    }

    std::string WindowFocusEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << (m_focused ? "window focused." : "window unfocused.");
        return ss.str();
    }

    std::string KeyEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_key << ", " << m_scancode << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        return ss.str();
    }

    std::string CharEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_codepoint;
        return ss.str();
    }

    std::string MouseButtonEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_button << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        return ss.str();
    }

    std::string MouseEnterEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << (m_entered ? "mouse entered." : "mouse exited.");
        return ss.str();
    }

    std::string MouseMovedEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

    std::string MouseScrolledEvent::string() const
    {
        std::stringstream ss {};
        ss.clear();
        ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
        return ss.str();
    }
}
