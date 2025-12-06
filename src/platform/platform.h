#pragma once

#include "JAGE/core.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    namespace Input
    {
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