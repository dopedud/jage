#include "platform/input.h"

#include "log.h"

namespace JAGE
{
    namespace Input
    {
        static GLFWwindow* glfw_handle;

        void SetActiveWindow(Window* window)
        {
            glfw_handle = static_cast<GLFWwindow*>(window->handle());
        }

        bool IsKeyPressed(KeyCode key)
        {
            int state { glfwGetKey(glfw_handle, ToGLFWKey(key)) };
            return state == GLFW_PRESS;
        }

        bool IsMouseButtonPressed(MouseButton button)
        {
            int state { glfwGetMouseButton(glfw_handle, ToGLFWMouseButton(button)) };
            return state == GLFW_PRESS;
        }

        std::pair<float, float> GetMousePosition()
        {
            double xpos, ypos;
            glfwGetCursorPos(glfw_handle, &xpos, &ypos);
            return std::pair<float, float>(xpos, ypos);
        }

        float GetMousePositionX() { return GetMousePosition().first; }
        float GetMousePositionY() { return GetMousePosition().second; }

        int ToGLFWKey(KeyCode key)
        {
            switch (key)
            {
                case JAGE_KEY_A: return GLFW_KEY_A; break;
                case JAGE_KEY_B: return GLFW_KEY_B; break;
                case JAGE_KEY_C: return GLFW_KEY_C; break;
                case JAGE_KEY_D: return GLFW_KEY_D; break;
                case JAGE_KEY_E: return GLFW_KEY_E; break;
                case JAGE_KEY_F: return GLFW_KEY_F; break;
                case JAGE_KEY_G: return GLFW_KEY_G; break;
                case JAGE_KEY_H: return GLFW_KEY_H; break;
                case JAGE_KEY_I: return GLFW_KEY_I; break;
                case JAGE_KEY_J: return GLFW_KEY_J; break;
                case JAGE_KEY_K: return GLFW_KEY_K; break;
                case JAGE_KEY_L: return GLFW_KEY_L; break;
                case JAGE_KEY_M: return GLFW_KEY_M; break;
                case JAGE_KEY_N: return GLFW_KEY_N; break;
                case JAGE_KEY_O: return GLFW_KEY_O; break;
                case JAGE_KEY_P: return GLFW_KEY_P; break;
                case JAGE_KEY_Q: return GLFW_KEY_Q; break;
                case JAGE_KEY_R: return GLFW_KEY_R; break;
                case JAGE_KEY_S: return GLFW_KEY_S; break;
                case JAGE_KEY_T: return GLFW_KEY_T; break;
                case JAGE_KEY_U: return GLFW_KEY_U; break;
                case JAGE_KEY_V: return GLFW_KEY_V; break;
                case JAGE_KEY_W: return GLFW_KEY_W; break;
                case JAGE_KEY_X: return GLFW_KEY_X; break;
                case JAGE_KEY_Y: return GLFW_KEY_Y; break;
                case JAGE_KEY_Z: return GLFW_KEY_Z; break;
                default: JAGE_LOG_ERROR("Key Conversion Error: unknown key {} from JAGE.", to_string(key)); return GLFW_KEY_UNKNOWN; break;
            }
        }

        int ToGLFWMouseButton(MouseButton button)
        {
            switch (button)
            {
                case JAGE_MOUSE_BUTTON_LEFT_CLICK:      return GLFW_MOUSE_BUTTON_LEFT; break;
                case JAGE_MOUSE_BUTTON_RIGHT_CLICK:     return GLFW_MOUSE_BUTTON_RIGHT; break;
                case JAGE_MOUSE_BUTTON_MIDDLE_CLICK:    return GLFW_MOUSE_BUTTON_MIDDLE; break;
                case JAGE_MOUSE_BUTTON_4:               return GLFW_MOUSE_BUTTON_4; break;
                case JAGE_MOUSE_BUTTON_5:               return GLFW_MOUSE_BUTTON_5; break;
            }
        }

        int ToGLFWAction(Action action)
        {
            switch (action)
            {
                case JAGE_ACTION_PRESSED:   return GLFW_PRESS; break;
                case JAGE_ACTION_RELEASED:  return GLFW_RELEASE; break;
                case JAGE_ACTION_REPEATED:  return GLFW_REPEAT; break;
            }
        }

        int ToGLFWMods(int mods)
        {
            // GLFW does not have a specific macro to indicate a none-modifier, 0 is assumed
            int glfw_mods {};

            if (mods & JAGE_MOD_SHIFT)      glfw_mods = glfw_mods | GLFW_MOD_SHIFT;
            if (mods & JAGE_MOD_CONTROL)    glfw_mods = glfw_mods | GLFW_MOD_CONTROL;
            if (mods & JAGE_MOD_ALT)        glfw_mods = glfw_mods | GLFW_MOD_ALT;
            if (mods & JAGE_MOD_SUPER)      glfw_mods = glfw_mods | GLFW_MOD_SUPER;

            return glfw_mods;
        }

        KeyCode FromGLFWKey(int key)
        {
            switch (key)
            {
                case GLFW_KEY_A: return JAGE_KEY_A; break;
                case GLFW_KEY_B: return JAGE_KEY_B; break;
                case GLFW_KEY_C: return JAGE_KEY_C; break;
                case GLFW_KEY_D: return JAGE_KEY_D; break;
                case GLFW_KEY_E: return JAGE_KEY_E; break;
                case GLFW_KEY_F: return JAGE_KEY_F; break;
                case GLFW_KEY_G: return JAGE_KEY_G; break;
                case GLFW_KEY_H: return JAGE_KEY_H; break;
                case GLFW_KEY_I: return JAGE_KEY_I; break;
                case GLFW_KEY_J: return JAGE_KEY_J; break;
                case GLFW_KEY_K: return JAGE_KEY_K; break;
                case GLFW_KEY_L: return JAGE_KEY_L; break;
                case GLFW_KEY_M: return JAGE_KEY_M; break;
                case GLFW_KEY_N: return JAGE_KEY_N; break;
                case GLFW_KEY_O: return JAGE_KEY_O; break;
                case GLFW_KEY_P: return JAGE_KEY_P; break;
                case GLFW_KEY_Q: return JAGE_KEY_Q; break;
                case GLFW_KEY_R: return JAGE_KEY_R; break;
                case GLFW_KEY_S: return JAGE_KEY_S; break;
                case GLFW_KEY_T: return JAGE_KEY_T; break;
                case GLFW_KEY_U: return JAGE_KEY_U; break;
                case GLFW_KEY_V: return JAGE_KEY_V; break;
                case GLFW_KEY_W: return JAGE_KEY_W; break;
                case GLFW_KEY_X: return JAGE_KEY_X; break;
                case GLFW_KEY_Y: return JAGE_KEY_Y; break;
                case GLFW_KEY_Z: return JAGE_KEY_Z; break;
                default: JAGE_LOG_ERROR("Key Conversion Error: unknown key numbered {} from GLFW.", key); return JAGE_KEY_UNKNOWN; break;
            }
        }

        MouseButton FromGLFWMouseButton(int button)
        {
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:    return JAGE_MOUSE_BUTTON_LEFT_CLICK; break;
                case GLFW_MOUSE_BUTTON_RIGHT:   return JAGE_MOUSE_BUTTON_RIGHT_CLICK; break;
                case GLFW_MOUSE_BUTTON_MIDDLE:  return JAGE_MOUSE_BUTTON_MIDDLE_CLICK; break;
                case GLFW_MOUSE_BUTTON_4:       return JAGE_MOUSE_BUTTON_4; break;
                case GLFW_MOUSE_BUTTON_5:       return JAGE_MOUSE_BUTTON_5; break;
            }
        }

        Action FromGLFWAction(int action)
        {
            switch (action)
            {
                case GLFW_PRESS:    return JAGE_ACTION_PRESSED; break;
                case GLFW_RELEASE:  return JAGE_ACTION_RELEASED; break;
                case GLFW_REPEAT:   return JAGE_ACTION_REPEATED; break;
            }
        }

        int FromGLFWMods(int mods)
        {
            int jage_mods { static_cast<int>(JAGE_MOD_NONE) };

            if (mods & GLFW_MOD_SHIFT)      jage_mods = jage_mods | JAGE_MOD_SHIFT;
            if (mods & GLFW_MOD_CONTROL)    jage_mods = jage_mods | JAGE_MOD_CONTROL;
            if (mods & GLFW_MOD_ALT)        jage_mods = jage_mods | JAGE_MOD_ALT;
            if (mods & GLFW_MOD_SUPER)      jage_mods = jage_mods | JAGE_MOD_SUPER;

            return jage_mods;
        }
    }
}