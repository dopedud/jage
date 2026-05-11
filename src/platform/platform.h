#pragma once

#include "JAGE/core.h"
#include "JAGE/renderer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    namespace Input
    {
        /**
         * @fn SetActiveWindow
         * @brief Sets the active window to query input from.
         * 
         * Querying input should only be for a single window at any given moment in time.
         * 
         * @param window The window to query input from. 
         * 
         * @{
         */
        void SetActiveWindow(GLFWwindow* window);
        /** @} */

        void UpdateMousePosition();

        int ToGLFWKey(KeyCode key);
        int ToGLFWMouseButton(MouseButton button);
        int ToGLFWAction(Action action);
        int ToGLFWMods(int mods);
        int ToGLFWCursorMode(CursorMode mode);

        KeyCode         FromGLFWKey(int key);
        MouseButton     FromGLFWMouseButton(int button);
        Action          FromGLFWAction(int action);
        int             FromGLFWMods(int mods);
        CursorMode      FromGLFWCursorMode(int mode);
    }
}