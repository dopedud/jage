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

        std::string_view to_string(KeyCode key)
        {
            switch(key)
            {
                case JAGE_KEY_A: return "A"; break;
                case JAGE_KEY_B: return "B"; break;
                case JAGE_KEY_C: return "C"; break;
                case JAGE_KEY_D: return "D"; break;
                case JAGE_KEY_E: return "E"; break;
                case JAGE_KEY_F: return "F"; break;
                case JAGE_KEY_G: return "G"; break;
                case JAGE_KEY_H: return "H"; break;
                case JAGE_KEY_I: return "I"; break;
                case JAGE_KEY_J: return "J"; break;
                case JAGE_KEY_K: return "K"; break;
                case JAGE_KEY_L: return "L"; break;
                case JAGE_KEY_M: return "M"; break;
                case JAGE_KEY_N: return "N"; break;
                case JAGE_KEY_O: return "O"; break;
                case JAGE_KEY_P: return "P"; break;
                case JAGE_KEY_Q: return "Q"; break;
                case JAGE_KEY_R: return "R"; break;
                case JAGE_KEY_S: return "S"; break;
                case JAGE_KEY_T: return "T"; break;
                case JAGE_KEY_U: return "U"; break;
                case JAGE_KEY_V: return "V"; break;
                case JAGE_KEY_W: return "W"; break;
                case JAGE_KEY_X: return "X"; break;
                case JAGE_KEY_Y: return "Y"; break;
                case JAGE_KEY_Z: return "Z"; break;
                default: JAGE_LOG_ERROR("ToString Error: unknown key numbered {}.", static_cast<int>(key)); return "UNKNOWN"; break;
            }
        }

        std::string_view to_string(MouseButton button)
        {
            switch(button)
            {
                case JAGE_MOUSE_BUTTON_LEFT_CLICK:      return "MOUSE LEFT CLICK"; break;
                case JAGE_MOUSE_BUTTON_RIGHT_CLICK:     return "MOUSE RIGHT CLICK"; break;
                case JAGE_MOUSE_BUTTON_MIDDLE_CLICK:    return "MOUSE MIDDLE CLICK"; break;
                case JAGE_MOUSE_BUTTON_4:               return "MOUSE BUTTON 4"; break;
                case JAGE_MOUSE_BUTTON_5:               return "MOUSE BUTTON 5"; break;
            }
        }

        std::string_view to_string(Action action)
        {
            switch(action)
            {
                case JAGE_ACTION_PRESSED:   return "PRESSED"; break;
                case JAGE_ACTION_RELEASED:  return "RELEASED"; break;
                case JAGE_ACTION_REPEATED:  return "REPEATED"; break;
            }
        }

        std::string_view to_string(int mods)
        {
            std::string str {};

            if (mods & JAGE_MOD_SHIFT)      str += "SHIFT, ";
            if (mods & JAGE_MOD_CONTROL)    str += "CONTROL, ";
            if (mods & JAGE_MOD_ALT)        str += "ALT, ";
            if (mods & JAGE_MOD_SUPER)      str += "SHIFT, ";

            if (str.size() > 0) str.erase(str.size() - 2);

            return str;
        }

        std::ostream& operator<<(std::ostream& os, const KeyCode& key)          { return os << to_string(key); }
        std::ostream& operator<<(std::ostream& os, const Action& action)        { return os << to_string(action); }
        std::ostream& operator<<(std::ostream& os, const MouseButton& button)   { return os << to_string(button); }
        std::ostream& operator<<(std::ostream& os, const int& mods)             { return os << to_string(mods); }
    }
}