#include "JAGE/core.h"

namespace JAGE
{
    static void encode_utf8(char* out, unsigned codepoint)
    {
        if (codepoint <= 0x7F)
        {
            out[0] = codepoint;
            out[1] = '\0';
        }

        else if (codepoint <= 0x7FF)
        {
            out[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
            out[1] = 0x80 | (codepoint & 0x3F);
            out[2] = '\0';
        }

        else if (codepoint <= 0xFFFF)
        {
            out[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
            out[1] = 0x80 | ((codepoint >> 6) & 0x3F);
            out[2] = 0x80 | (codepoint & 0x3F);
            out[3] = '\0';
        }

        else if (codepoint <= 0x10FFFF)
        {
            out[0] = 0xF0 | ((codepoint >> 18) & 0x07);
            out[1] = 0x80 | ((codepoint >> 12) & 0x3F);
            out[2] = 0x80 | ((codepoint >> 6) & 0x3F);
            out[3] = 0x80 | (codepoint & 0x3F);
            out[4] = '\0';
        }
    }

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

    std::string WindowResizeEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_width << ", " << m_height;
        return ss.str();
    }

    std::string WindowFocusEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << (m_focused ? "window focused." : "window unfocused.");
        return ss.str();
    }

    std::string KeyEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_key << ", " << m_scancode << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        return ss.str();
    }

    std::string CharEvent::to_string() const
    {
        char utf8_str[5] { 0 };
        encode_utf8(utf8_str, m_codepoint);

        std::stringstream ss;
        ss << name() << "Event: " << m_codepoint;
        return ss.str();
    }

    std::string MouseButtonEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_button << ", " << m_action << ", ";
        Input::operator<<(ss, m_mods);
        return ss.str();
    }

    std::string MouseEnterEvent::to_string() const 
    {
        std::stringstream ss;
        ss << name() << "Event: " << (m_entered ? "mouse entered." : "mouse exited."); 
        return ss.str();
    }

    std::string MouseMovedEvent::to_string() const
    {
        std::stringstream ss;
        ss << name() << "Event: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

    std::string MouseScrolledEvent::to_string() const
    {
        std::stringstream ss;
        ss.str() = "";
        ss << name() << "Event: " << m_offsetX << ", " << m_offsetY;
        return ss.str();
    }
}
