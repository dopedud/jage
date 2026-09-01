#include "platform/platform.h"

#include "log.h"

namespace JAGE
{
    namespace Input
    {
        static GLFWwindow* glfw_handle;

        static double previous_mouse_positionX {}, previous_mouse_positionY {};
        static double current_mouse_positionX {}, current_mouse_positionY {};

        void SetActiveWindow(GLFWwindow* window) { glfw_handle = window; }

        bool IsKeyPressed(KeyCode key)
        {
            int state { glfwGetKey(glfw_handle, ToGLFWKey(key)) };
            return state == GLFW_PRESS;
        }

        bool IsKeyReleased(KeyCode key)
        {
            int state { glfwGetKey(glfw_handle, ToGLFWKey(key)) };
            return state == GLFW_RELEASE;
        }

        bool IsMouseButtonPressed(MouseButton button)
        {
            int state { glfwGetMouseButton(glfw_handle, ToGLFWMouseButton(button)) };
            return state == GLFW_PRESS;
        }

        bool IsMouseButtonReleased(MouseButton button)
        {
            int state { glfwGetMouseButton(glfw_handle, ToGLFWMouseButton(button)) };
            return state == GLFW_RELEASE;
        }
        
        void SetCursorMode(CursorMode mode) { glfwSetInputMode(glfw_handle, GLFW_CURSOR, ToGLFWCursorMode(mode)); }
        CursorMode GetCursorMode() { return FromGLFWCursorMode(glfwGetInputMode(glfw_handle, GLFW_CURSOR)); }

        float GetMousePositionX() { return current_mouse_positionX; }
        float GetMousePositionY() { return current_mouse_positionY; }
        float GetMousePositionDeltaX() { return current_mouse_positionX - previous_mouse_positionX; }
        float GetMousePositionDeltaY() { return current_mouse_positionY - previous_mouse_positionY; }

        void UpdateMousePosition()
        {
            previous_mouse_positionX = current_mouse_positionX;
            previous_mouse_positionY = current_mouse_positionY;
            glfwGetCursorPos(glfw_handle, &current_mouse_positionX, &current_mouse_positionY);
        }

        //
        // REALLY LONG CONVERSIONS LIST
        //

        DISABLE_WARNING_PUSH
        DISABLE_WARNING_GCC_CLANG("-Wreturn-type")
        DISABLE_WARNING_GCC_CLANG("-Wswitch")

        int ToGLFWKey(KeyCode key)
        {
            switch (key)
            {
                case JAGE_KEY_A: return GLFW_KEY_A;
                case JAGE_KEY_B: return GLFW_KEY_B;
                case JAGE_KEY_C: return GLFW_KEY_C;
                case JAGE_KEY_D: return GLFW_KEY_D;
                case JAGE_KEY_E: return GLFW_KEY_E;
                case JAGE_KEY_F: return GLFW_KEY_F;
                case JAGE_KEY_G: return GLFW_KEY_G;
                case JAGE_KEY_H: return GLFW_KEY_H;
                case JAGE_KEY_I: return GLFW_KEY_I;
                case JAGE_KEY_J: return GLFW_KEY_J;
                case JAGE_KEY_K: return GLFW_KEY_K;
                case JAGE_KEY_L: return GLFW_KEY_L;
                case JAGE_KEY_M: return GLFW_KEY_M;
                case JAGE_KEY_N: return GLFW_KEY_N;
                case JAGE_KEY_O: return GLFW_KEY_O;
                case JAGE_KEY_P: return GLFW_KEY_P;
                case JAGE_KEY_Q: return GLFW_KEY_Q;
                case JAGE_KEY_R: return GLFW_KEY_R;
                case JAGE_KEY_S: return GLFW_KEY_S;
                case JAGE_KEY_T: return GLFW_KEY_T;
                case JAGE_KEY_U: return GLFW_KEY_U;
                case JAGE_KEY_V: return GLFW_KEY_V;
                case JAGE_KEY_W: return GLFW_KEY_W;
                case JAGE_KEY_X: return GLFW_KEY_X;
                case JAGE_KEY_Y: return GLFW_KEY_Y;
                case JAGE_KEY_Z: return GLFW_KEY_Z;

                case JAGE_KEY_1: return GLFW_KEY_1;
                case JAGE_KEY_2: return GLFW_KEY_2;
                case JAGE_KEY_3: return GLFW_KEY_3;
                case JAGE_KEY_4: return GLFW_KEY_4;
                case JAGE_KEY_5: return GLFW_KEY_5;
                case JAGE_KEY_6: return GLFW_KEY_6;
                case JAGE_KEY_7: return GLFW_KEY_7;
                case JAGE_KEY_8: return GLFW_KEY_8;
                case JAGE_KEY_9: return GLFW_KEY_9;
                case JAGE_KEY_0: return GLFW_KEY_0;

                case JAGE_KEY_SPACE:                    return GLFW_KEY_SPACE;
                case JAGE_KEY_COMMA:                    return GLFW_KEY_COMMA;
                case JAGE_KEY_PERIOD:                   return GLFW_KEY_PERIOD;
                case JAGE_KEY_FORWARDSLASH:             return GLFW_KEY_SLASH; 
                case JAGE_KEY_SEMICOLON:                return GLFW_KEY_SEMICOLON;
                case JAGE_KEY_APOSTROPHE:               return GLFW_KEY_APOSTROPHE;
                case JAGE_KEY_LEFT_SQUARE_BRACKET:      return GLFW_KEY_LEFT_BRACKET;
                case JAGE_KEY_RIGHT_SQUARE_BRACKET:     return GLFW_KEY_RIGHT_BRACKET;
                case JAGE_KEY_BACKSLASH:                return GLFW_KEY_BACKSLASH;
                case JAGE_KEY_GRAVE_ACCENT:             return GLFW_KEY_GRAVE_ACCENT;
                case JAGE_KEY_MINUS:                    return GLFW_KEY_MINUS;
                case JAGE_KEY_EQUAL:                    return GLFW_KEY_EQUAL;

                case JAGE_KEY_ENTER:        return GLFW_KEY_ENTER;
                case JAGE_KEY_ESCAPE:       return GLFW_KEY_ESCAPE;
                case JAGE_KEY_BACKSPACE:    return GLFW_KEY_BACKSPACE;
                case JAGE_KEY_TAB:          return GLFW_KEY_TAB;
                case JAGE_KEY_CAPS_LOCK:    return GLFW_KEY_CAPS_LOCK;

                case JAGE_KEY_LEFT_ARROW:   return GLFW_KEY_LEFT;
                case JAGE_KEY_RIGHT_ARROW:  return GLFW_KEY_RIGHT;
                case JAGE_KEY_UP_ARROW:     return GLFW_KEY_UP;
                case JAGE_KEY_DOWN_ARROW:   return GLFW_KEY_DOWN;

                case JAGE_KEY_LEFT_SHIFT:       return GLFW_KEY_LEFT_SHIFT;
                case JAGE_KEY_RIGHT_SHIFT:      return GLFW_KEY_RIGHT_SHIFT;
                case JAGE_KEY_LEFT_CONTROL:     return GLFW_KEY_LEFT_CONTROL;
                case JAGE_KEY_RIGHT_CONTROL:    return GLFW_KEY_RIGHT_CONTROL;
                case JAGE_KEY_LEFT_ALT:         return GLFW_KEY_LEFT_ALT;
                case JAGE_KEY_RIGHT_ALT:        return GLFW_KEY_RIGHT_ALT;

                case JAGE_KEY_F1:   return GLFW_KEY_F1;
                case JAGE_KEY_F2:   return GLFW_KEY_F2;
                case JAGE_KEY_F3:   return GLFW_KEY_F3;
                case JAGE_KEY_F4:   return GLFW_KEY_F4;
                case JAGE_KEY_F5:   return GLFW_KEY_F5;
                case JAGE_KEY_F6:   return GLFW_KEY_F6;
                case JAGE_KEY_F7:   return GLFW_KEY_F7;
                case JAGE_KEY_F8:   return GLFW_KEY_F8;
                case JAGE_KEY_F9:   return GLFW_KEY_F9;
                case JAGE_KEY_F10:  return GLFW_KEY_F10;
                case JAGE_KEY_F11:  return GLFW_KEY_F11;
                case JAGE_KEY_F12:  return GLFW_KEY_F12;

                case JAGE_KEY_KP1:  return GLFW_KEY_KP_1;
                case JAGE_KEY_KP2:  return GLFW_KEY_KP_2;
                case JAGE_KEY_KP3:  return GLFW_KEY_KP_3;
                case JAGE_KEY_KP4:  return GLFW_KEY_KP_4;
                case JAGE_KEY_KP5:  return GLFW_KEY_KP_5;
                case JAGE_KEY_KP6:  return GLFW_KEY_KP_6;
                case JAGE_KEY_KP7:  return GLFW_KEY_KP_7;
                case JAGE_KEY_KP8:  return GLFW_KEY_KP_8;
                case JAGE_KEY_KP9:  return GLFW_KEY_KP_9;
                case JAGE_KEY_KP0:  return GLFW_KEY_KP_0;
            }

            JAGE_LOG_ERROR("Key Conversion Error: unknown key {} from JAGE.", to_string(key)); return GLFW_KEY_UNKNOWN;
        }

        int ToGLFWMouseButton(MouseButton button)
        {
            switch (button)
            {
                case JAGE_MOUSE_BUTTON_LEFT_CLICK:      return GLFW_MOUSE_BUTTON_LEFT;
                case JAGE_MOUSE_BUTTON_RIGHT_CLICK:     return GLFW_MOUSE_BUTTON_RIGHT;
                case JAGE_MOUSE_BUTTON_MIDDLE_CLICK:    return GLFW_MOUSE_BUTTON_MIDDLE;
                case JAGE_MOUSE_BUTTON_4:               return GLFW_MOUSE_BUTTON_4;
                case JAGE_MOUSE_BUTTON_5:               return GLFW_MOUSE_BUTTON_5;
            }
        }

        int ToGLFWAction(Action action)
        {
            switch (action)
            {
                case JAGE_ACTION_PRESSED:   return GLFW_PRESS;
                case JAGE_ACTION_RELEASED:  return GLFW_RELEASE;
                case JAGE_ACTION_REPEATED:  return GLFW_REPEAT;
            }
        }

        int ToGLFWMods(int mods)
        {
            // GLFW does not have a specific macro to indicate a none-modifier, 0 is assumed
            int glfw_mods {};

            if (mods & JAGE_MOD_SHIFT)      glfw_mods = glfw_mods | GLFW_MOD_SHIFT;
            if (mods & JAGE_MOD_CONTROL)    glfw_mods = glfw_mods | GLFW_MOD_CONTROL;
            if (mods & JAGE_MOD_ALT)        glfw_mods = glfw_mods | GLFW_MOD_ALT;

            return glfw_mods;
        }

        int ToGLFWCursorMode(CursorMode mode)
        {
            switch (mode)
            {
                case JAGE_CURSOR_MODE_NORMAL:       return GLFW_CURSOR_NORMAL;
                case JAGE_CURSOR_MODE_DISABLED:     return GLFW_CURSOR_DISABLED;
                case JAGE_CURSOR_MODE_HIDDEN:       return GLFW_CURSOR_HIDDEN;
            }
        }

        KeyCode FromGLFWKey(int key)
        {
            switch (key)
            {
                case GLFW_KEY_A: return JAGE_KEY_A;
                case GLFW_KEY_B: return JAGE_KEY_B;
                case GLFW_KEY_C: return JAGE_KEY_C;
                case GLFW_KEY_D: return JAGE_KEY_D;
                case GLFW_KEY_E: return JAGE_KEY_E;
                case GLFW_KEY_F: return JAGE_KEY_F;
                case GLFW_KEY_G: return JAGE_KEY_G;
                case GLFW_KEY_H: return JAGE_KEY_H;
                case GLFW_KEY_I: return JAGE_KEY_I;
                case GLFW_KEY_J: return JAGE_KEY_J;
                case GLFW_KEY_K: return JAGE_KEY_K;
                case GLFW_KEY_L: return JAGE_KEY_L;
                case GLFW_KEY_M: return JAGE_KEY_M;
                case GLFW_KEY_N: return JAGE_KEY_N;
                case GLFW_KEY_O: return JAGE_KEY_O;
                case GLFW_KEY_P: return JAGE_KEY_P;
                case GLFW_KEY_Q: return JAGE_KEY_Q;
                case GLFW_KEY_R: return JAGE_KEY_R;
                case GLFW_KEY_S: return JAGE_KEY_S;
                case GLFW_KEY_T: return JAGE_KEY_T;
                case GLFW_KEY_U: return JAGE_KEY_U;
                case GLFW_KEY_V: return JAGE_KEY_V;
                case GLFW_KEY_W: return JAGE_KEY_W;
                case GLFW_KEY_X: return JAGE_KEY_X;
                case GLFW_KEY_Y: return JAGE_KEY_Y;
                case GLFW_KEY_Z: return JAGE_KEY_Z;

                case GLFW_KEY_1: return JAGE_KEY_1;
                case GLFW_KEY_2: return JAGE_KEY_2;
                case GLFW_KEY_3: return JAGE_KEY_3;
                case GLFW_KEY_4: return JAGE_KEY_4;
                case GLFW_KEY_5: return JAGE_KEY_5;
                case GLFW_KEY_6: return JAGE_KEY_6;
                case GLFW_KEY_7: return JAGE_KEY_7;
                case GLFW_KEY_8: return JAGE_KEY_8;
                case GLFW_KEY_9: return JAGE_KEY_9;
                case GLFW_KEY_0: return JAGE_KEY_0;

                case GLFW_KEY_SPACE:            return JAGE_KEY_SPACE;
                case GLFW_KEY_COMMA:            return JAGE_KEY_COMMA;
                case GLFW_KEY_PERIOD:           return JAGE_KEY_PERIOD;
                case GLFW_KEY_SLASH:            return JAGE_KEY_FORWARDSLASH;
                case GLFW_KEY_SEMICOLON:        return JAGE_KEY_SEMICOLON;
                case GLFW_KEY_APOSTROPHE:       return JAGE_KEY_APOSTROPHE;
                case GLFW_KEY_LEFT_BRACKET:     return JAGE_KEY_LEFT_SQUARE_BRACKET;
                case GLFW_KEY_RIGHT_BRACKET:    return JAGE_KEY_RIGHT_SQUARE_BRACKET;
                case GLFW_KEY_BACKSLASH:        return JAGE_KEY_BACKSLASH;
                case GLFW_KEY_GRAVE_ACCENT:     return JAGE_KEY_GRAVE_ACCENT;
                case GLFW_KEY_MINUS:            return JAGE_KEY_MINUS;
                case GLFW_KEY_EQUAL:            return JAGE_KEY_EQUAL;

                case GLFW_KEY_ENTER:        return JAGE_KEY_ENTER;
                case GLFW_KEY_ESCAPE:       return JAGE_KEY_ESCAPE;
                case GLFW_KEY_BACKSPACE:    return JAGE_KEY_BACKSPACE;
                case GLFW_KEY_TAB:          return JAGE_KEY_TAB;
                case GLFW_KEY_CAPS_LOCK:    return JAGE_KEY_CAPS_LOCK;

                case GLFW_KEY_LEFT:   return JAGE_KEY_LEFT_ARROW;
                case GLFW_KEY_RIGHT:  return JAGE_KEY_RIGHT_ARROW;
                case GLFW_KEY_UP:     return JAGE_KEY_UP_ARROW;
                case GLFW_KEY_DOWN:   return JAGE_KEY_DOWN_ARROW;

                case GLFW_KEY_LEFT_SHIFT:       return JAGE_KEY_LEFT_SHIFT;
                case GLFW_KEY_RIGHT_SHIFT:      return JAGE_KEY_RIGHT_SHIFT;
                case GLFW_KEY_LEFT_CONTROL:     return JAGE_KEY_LEFT_CONTROL;
                case GLFW_KEY_RIGHT_CONTROL:    return JAGE_KEY_RIGHT_CONTROL;
                case GLFW_KEY_LEFT_ALT:         return JAGE_KEY_LEFT_ALT;
                case GLFW_KEY_RIGHT_ALT:        return JAGE_KEY_RIGHT_ALT;

                case GLFW_KEY_F1:   return JAGE_KEY_F1;
                case GLFW_KEY_F2:   return JAGE_KEY_F2;
                case GLFW_KEY_F3:   return JAGE_KEY_F3;
                case GLFW_KEY_F4:   return JAGE_KEY_F4;
                case GLFW_KEY_F5:   return JAGE_KEY_F5;
                case GLFW_KEY_F6:   return JAGE_KEY_F6;
                case GLFW_KEY_F7:   return JAGE_KEY_F7;
                case GLFW_KEY_F8:   return JAGE_KEY_F8;
                case GLFW_KEY_F9:   return JAGE_KEY_F9;
                case GLFW_KEY_F10:  return JAGE_KEY_F10;
                case GLFW_KEY_F11:  return JAGE_KEY_F11;
                case GLFW_KEY_F12:  return JAGE_KEY_F12;

                case GLFW_KEY_KP_1:  return JAGE_KEY_KP1;
                case GLFW_KEY_KP_2:  return JAGE_KEY_KP2;
                case GLFW_KEY_KP_3:  return JAGE_KEY_KP3;
                case GLFW_KEY_KP_4:  return JAGE_KEY_KP4;
                case GLFW_KEY_KP_5:  return JAGE_KEY_KP5;
                case GLFW_KEY_KP_6:  return JAGE_KEY_KP6;
                case GLFW_KEY_KP_7:  return JAGE_KEY_KP7;
                case GLFW_KEY_KP_8:  return JAGE_KEY_KP8;
                case GLFW_KEY_KP_9:  return JAGE_KEY_KP9;
                case GLFW_KEY_KP_0:  return JAGE_KEY_KP0;
            }

           JAGE_LOG_ERROR("Key Conversion Error: unknown key numbered {} from GLFW.", key); return JAGE_KEY_UNKNOWN;
        }

        MouseButton FromGLFWMouseButton(int button)
        {
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:    return JAGE_MOUSE_BUTTON_LEFT_CLICK;
                case GLFW_MOUSE_BUTTON_RIGHT:   return JAGE_MOUSE_BUTTON_RIGHT_CLICK;
                case GLFW_MOUSE_BUTTON_MIDDLE:  return JAGE_MOUSE_BUTTON_MIDDLE_CLICK;
                case GLFW_MOUSE_BUTTON_4:       return JAGE_MOUSE_BUTTON_4;
                case GLFW_MOUSE_BUTTON_5:       return JAGE_MOUSE_BUTTON_5;
            }
        }

        Action FromGLFWAction(int action)
        {
            switch (action)
            {
                case GLFW_PRESS:    return JAGE_ACTION_PRESSED;
                case GLFW_RELEASE:  return JAGE_ACTION_RELEASED;
                case GLFW_REPEAT:   return JAGE_ACTION_REPEATED;
            }
        }

        int FromGLFWMods(int mods)
        {
            int jage_mods { static_cast<int>(JAGE_MOD_NONE) };

            if (mods & GLFW_MOD_SHIFT)      jage_mods = jage_mods | JAGE_MOD_SHIFT;
            if (mods & GLFW_MOD_CONTROL)    jage_mods = jage_mods | JAGE_MOD_CONTROL;
            if (mods & GLFW_MOD_ALT)        jage_mods = jage_mods | JAGE_MOD_ALT;

            return jage_mods;
        }

        CursorMode FromGLFWCursorMode(int mode)
        {
            switch (mode)
            {
                case GLFW_CURSOR_NORMAL:    return JAGE_CURSOR_MODE_NORMAL;
                case GLFW_CURSOR_DISABLED:  return JAGE_CURSOR_MODE_DISABLED;
                case GLFW_CURSOR_HIDDEN:    return JAGE_CURSOR_MODE_HIDDEN;
            }
        }

        DISABLE_WARNING_POP

        //
        // END REALLY LONG CONVERSIONS LIST
        //
    }
}
