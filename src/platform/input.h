#pragma once

#include "JAGE/core.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace JAGE
{
    namespace Input
    {
        int ToGLFWKey(KeyCode key);
        int ToGLFWMouseButton(MouseButton button);
        int ToGLFWAction(Action action);
        int ToGLFWMods(int mods);

        KeyCode         FromGLFWKey(int key);
        MouseButton     FromGLFWMouseButton(int button);
        Action          FromGLFWAction(int action);
        int             FromGLFWMods(int mods);
    }
}