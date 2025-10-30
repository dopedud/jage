#include "JAGE/core.h"

#include "log.h"

namespace JAGE
{
    namespace Input
    {
        int operator&(Modifier lhs, Modifier rhs)
        {
            int lhs_casted { static_cast<int>(lhs) };
            int rhs_casted { static_cast<int>(rhs) };
            return lhs_casted & rhs_casted;
        }

        int operator|(Modifier lhs, Modifier rhs)
        {
            int lhs_casted { static_cast<int>(lhs) };
            int rhs_casted { static_cast<int>(rhs) };
            return lhs_casted | rhs_casted;
        }

        int operator&(Modifier lhs, int rhs)
        {
            int lhs_casted { static_cast<int>(lhs) };
            return lhs_casted & rhs;
        }

        int operator|(Modifier lhs, int rhs)
        {
            int lhs_casted { static_cast<int>(lhs) };
            return lhs_casted | rhs;
        }

        int operator&(int lhs, Modifier rhs)
        {
            int rhs_casted { static_cast<int>(rhs) };
            return lhs & rhs_casted;
        }

        int operator|(int lhs, Modifier rhs)
        {
            int rhs_casted { static_cast<int>(rhs) };
            return lhs | rhs_casted;
        }

        DISABLE_WARNING_PUSH
        DISABLE_WARNING_GCC_CLANG("-Wreturn-type")
        DISABLE_WARNING_GCC_CLANG("-Wswitch")

        std::string to_string(KeyCode key)
        {
            switch(key)
            {
                case JAGE_KEY_A: return "A";
                case JAGE_KEY_B: return "B";
                case JAGE_KEY_C: return "C";
                case JAGE_KEY_D: return "D";
                case JAGE_KEY_E: return "E";
                case JAGE_KEY_F: return "F";
                case JAGE_KEY_G: return "G";
                case JAGE_KEY_H: return "H";
                case JAGE_KEY_I: return "I";
                case JAGE_KEY_J: return "J";
                case JAGE_KEY_K: return "K";
                case JAGE_KEY_L: return "L";
                case JAGE_KEY_M: return "M";
                case JAGE_KEY_N: return "N";
                case JAGE_KEY_O: return "O";
                case JAGE_KEY_P: return "P";
                case JAGE_KEY_Q: return "Q";
                case JAGE_KEY_R: return "R";
                case JAGE_KEY_S: return "S";
                case JAGE_KEY_T: return "T";
                case JAGE_KEY_U: return "U";
                case JAGE_KEY_V: return "V";
                case JAGE_KEY_W: return "W";
                case JAGE_KEY_X: return "X";
                case JAGE_KEY_Y: return "Y";
                case JAGE_KEY_Z: return "Z";

                case JAGE_KEY_1: return "1";
                case JAGE_KEY_2: return "2";
                case JAGE_KEY_3: return "3";
                case JAGE_KEY_4: return "4";
                case JAGE_KEY_5: return "5";
                case JAGE_KEY_6: return "6";
                case JAGE_KEY_7: return "7";
                case JAGE_KEY_8: return "8";
                case JAGE_KEY_9: return "9";
                case JAGE_KEY_0: return "0";

                case JAGE_KEY_SPACE:                    return "SPACE";
                case JAGE_KEY_COMMA:                    return "COMMA";
                case JAGE_KEY_PERIOD:                   return "PERIOD";
                case JAGE_KEY_FORWARDSLASH:             return "FORWARDSLASH";
                case JAGE_KEY_SEMICOLON:                return "SEMICOLON";
                case JAGE_KEY_APOSTROPHE:               return "APOSTROPHE";
                case JAGE_KEY_LEFT_SQUARE_BRACKET:      return "LEFT_SQUARE_BRACKET";
                case JAGE_KEY_RIGHT_SQUARE_BRACKET:     return "RIGHT_SQUARE_BRACKET";
                case JAGE_KEY_BACKSLASH:                return "BACKSLASH";
                case JAGE_KEY_GRAVE_ACCENT:             return "GRAVE_ACCENT";
                case JAGE_KEY_MINUS:                    return "MINUS";
                case JAGE_KEY_EQUAL:                    return "EQUAL";

                case JAGE_KEY_ENTER:        return "ENTER";
                case JAGE_KEY_ESCAPE:       return "ESCAPE";
                case JAGE_KEY_BACKSPACE:    return "BACKSPACE";
                case JAGE_KEY_TAB:          return "TAB";
                case JAGE_KEY_CAPS_LOCK:    return "CAPS_LOCK";

                case JAGE_KEY_LEFT_ARROW:   return "LEFT_ARROW";
                case JAGE_KEY_RIGHT_ARROW:  return "RIGHT_ARROW";
                case JAGE_KEY_UP_ARROW:     return "UP_ARROW";
                case JAGE_KEY_DOWN_ARROW:   return "DOWN_ARROW";

                case JAGE_KEY_LEFT_SHIFT:       return "LEFT_SHIFT";
                case JAGE_KEY_RIGHT_SHIFT:      return "RIGHT_SHIFT";
                case JAGE_KEY_LEFT_CONTROL:     return "LEFT_CONTROL";
                case JAGE_KEY_RIGHT_CONTROL:    return "RIGHT_CONTROL";
                case JAGE_KEY_LEFT_ALT:         return "LEFT_ALT";
                case JAGE_KEY_RIGHT_ALT:        return "RIGHT_ALT";

                case JAGE_KEY_F1:   return "F1";
                case JAGE_KEY_F2:   return "F2";
                case JAGE_KEY_F3:   return "F3";
                case JAGE_KEY_F4:   return "F4";
                case JAGE_KEY_F5:   return "F5";
                case JAGE_KEY_F6:   return "F6";
                case JAGE_KEY_F7:   return "F7";
                case JAGE_KEY_F8:   return "F8";
                case JAGE_KEY_F9:   return "F9";
                case JAGE_KEY_F10:  return "F10";
                case JAGE_KEY_F11:  return "F11";
                case JAGE_KEY_F12:  return "F12";

                case JAGE_KEY_KP1: return "KP1";
                case JAGE_KEY_KP2: return "KP2";
                case JAGE_KEY_KP3: return "KP3";
                case JAGE_KEY_KP4: return "KP4";
                case JAGE_KEY_KP5: return "KP5";
                case JAGE_KEY_KP6: return "KP6";
                case JAGE_KEY_KP7: return "KP7";
                case JAGE_KEY_KP8: return "KP8";
                case JAGE_KEY_KP9: return "KP9";
                case JAGE_KEY_KP0: return "KP0";
            }

            JAGE_LOG_ERROR("ToString Error: unknown key numbered {}.", static_cast<int>(key)); return "UNKNOWN";
        }

        std::string to_string(MouseButton button)
        {
            switch(button)
            {
                case JAGE_MOUSE_BUTTON_LEFT_CLICK:      return "MOUSE LEFT CLICK";
                case JAGE_MOUSE_BUTTON_RIGHT_CLICK:     return "MOUSE RIGHT CLICK";
                case JAGE_MOUSE_BUTTON_MIDDLE_CLICK:    return "MOUSE MIDDLE CLICK";
                case JAGE_MOUSE_BUTTON_4:               return "MOUSE BUTTON 4";
                case JAGE_MOUSE_BUTTON_5:               return "MOUSE BUTTON 5";
            }
        }

        std::string to_string(Action action)
        {
            switch(action)
            {
                case JAGE_ACTION_PRESSED:   return "PRESSED";
                case JAGE_ACTION_RELEASED:  return "RELEASED";
                case JAGE_ACTION_REPEATED:  return "REPEATED";
            }
        }

        std::string to_string(int mods)
        {
            static std::string str {};

            // reset str since it's a static variable
            str = "";

            if (mods & JAGE_MOD_SHIFT)      str += "SHIFT, ";
            if (mods & JAGE_MOD_CONTROL)    str += "CONTROL, ";
            if (mods & JAGE_MOD_ALT)        str += "ALT, ";

            if (str.size() > 0) str.erase(str.size() - 2);

            return str;
        }

        DISABLE_WARNING_POP

        std::ostream& operator<<(std::ostream& os, const KeyCode& key)          { return os << to_string(key); }
        std::ostream& operator<<(std::ostream& os, const Action& action)        { return os << to_string(action); }
        std::ostream& operator<<(std::ostream& os, const MouseButton& button)   { return os << to_string(button); }
        std::ostream& operator<<(std::ostream& os, const int& mods)             { return os << to_string(mods); }
    }
}
