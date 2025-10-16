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

    std::string_view WindowResizeEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_width << ", " << m_height;
        return ss.str();
    }

    std::string_view WindowFocusEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << (m_focused ? "window focused." : "window unfocused.");
        return ss.str();
    }

    std::string_view KeyEvent::to_string() const
    {
        std::stringstream ss;
        // ss << name() << "Event: " << m_key << ", " << m_scancode << ", " << m_action << ", " << m_mods;

        ss << name() << "Event: ";
        Input::operator<<(ss, m_key) << ", ";
        ss << m_scancode << ", ";
        Input::operator<<(ss, m_action) << ", ";
        Input::operator<<(ss, m_mods);

        return ss.str();
    }

    std::string_view CharEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_codepoint;
        return ss.str();
    }

    std::string_view MouseButtonEvent::to_string() const
    {
        std::stringstream ss;
        // ss << name() << "Event: " << m_button << ", " << m_action << ", " << m_mods;

        ss << name() << "Event: ";
        Input::operator<<(ss, m_button) << ", ";
        Input::operator<<(ss, m_action) << ", ";
        Input::operator<<(ss, m_mods);

        return ss.str();
    }

    std::string_view MouseEnterEvent::to_string() const 
    {
        std::stringstream ss;
        ss << name() << "Event: " << (m_entered ? "mouse entered." : "mouse exited."); 
        return ss.str();
    }

    std::string_view MouseMovedEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

    std::string_view MouseScrolledEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
        return ss.str();
    }
}