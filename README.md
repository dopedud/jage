# JAGE (Just Another Game Engine) - Game Engine from Scratch

## About

This repository is a project about making a game engine from scratch.

JAGE focuses on exposing as much game development tools as possible to the user
to allow for maximum control, while also abstracting away low-level
implementations and maintain extensibility as much as possible to present a
friendly and easy-to-use interface.

## Table of Contents

- [Technology Stack](#technology-stack)
- [Getting Started](#getting-started)
    - [Basic Overview](#basic-overview)
    - [Basic Example](#basic-example)
- [Build and Installation](#build-and-installation)
- [Documentation Generation](#documentation-generation)

## Technology Stack

- **Programming Language(s):**      C++
- **Build System:**                 CMake
- **Logging:**                      spdlog
- **Windowing/Input Management:**   GLFW
- **Rendering:**                    OpenGL
- **Asset Management:**             Assimp, stb_image, xxhash
- **Mathematics:**                  GL Mathematics
- **Scene Management (ECS):**       flecs
- **Game GUI:**                     TBD
- **Editor GUI:**                   Dear ImGui
- **Code Documentation:**           Doxygen

## Getting Started

### Basic Overview

JAGE can act as a framework where developers can take control of low-level
systems commonly used in a game engine by providing the necessary header files
and CMake build scripts to let them build the game executable from the ground
up, but it can also act as a friendly interface for developers who are just
starting out, or for those who are looking to make actual games instead of
reinventing the wheel by providing them with an editor (soon!) where they can
build their game world, code behaviours in their game, and manage projects
accordingly.

### Basic Example

You can start by coding the example below in the client side:

```cpp
#include "JAGE/core.h"
#include "JAGE/layers.h"
#include "JAGE/math.h"

int main(int argc, char** argv)
{
    // initialise the engine (mostly on logging and asset management)
    JAGE::Init(argc, argv);

    // have your own variable to dictate whether to run the game loop or not
    bool running { true };

    // JAGE provides logging utilities for both the application and the engine
    // (although it's private for the engine)
    APP_MSG_TRACE("Creating a window.");

    // set your own window properties like width and height of the window and
    // the title (optional)
    JAGE::WindowProperties window_properties {};
    std::unique_ptr<JAGE::Window> window { JAGE::Window::Create(window_properties) };

    // you can push your own layer, or use the provided game layer that renders
    // the game world
    window->PushLayer(new JAGE::GameLayer{ window.get() });

    // have a callback function to receive JAGE's WindowCloseEvent event to
    // switch running to false
    std::function<bool(const JAGE::WindowCloseEvent&)> OnWindowClose
    {
        [&running](const JAGE::WindowCloseEvent& e) -> bool
        {
            running = false;
            return true;
        }
    };

    APP_MSG_TRACE("Setting event callback for window.");
    window->set_eventcallback([OnWindowClose](const JAGE::Event& e) -> void
    {
        JAGE::EventDispatcher dispatcher { e };
        dispatcher.dispatch<JAGE::WindowCloseEvent>(OnWindowClose);
    });

    // cap your application FPS (optional)
    JAGE::Time::SetTargetFPS(60);

    APP_MSG_TRACE("Running the game loop.");
    while (running)
    {
        window->OnUpdate();
    }

    APP_MSG_INFO("Exiting application.");

    // clean up resources (optional)
    window.reset();
    JAGE::Destroy();

    return 0;
}
```

For a more detailed view on how to use JAGE effectively, refer to the separate
[Overview](./docs/overview.md) section located in the `overview.md` file.

## Build and Installation

This project uses CMake to build, which requires the use of `CMakePresets.json`
and `CMakeUserPresets.json` file. The `CMakePresets.json` defines the general
CMake configurations and is needed so that `CMakeUserPresets.json` can derive
its configurations from it. The `CMakeUserPresets.json` is a file that contains
developer-specific CMake configurations, which means each developer who wishes
to contribute should define their own `CMakeUserPresets.json`. A template is
provided as shown below:

```json
{
    "name": "user_debug",
    "inherits": "debug",
    "displayName": "Debug Config (User)",
    "generator": "MinGW Makefiles",
    "cacheVariables":
    {
        "CMAKE_C_COMPILER": "C:/msys64/ucrt64/bin/gcc.exe",
        "CMAKE_CXX_COMPILER": "C:/msys64/ucrt64/bin/g++.exe",
        "CMAKE_MAKE_PROGRAM": "C:/msys64/ucrt64/bin/mingw32-make.exe"
    }
},

{
    "name": "user_release",
    "inherits": "release",
    "displayName": "Release Config (User)", 
    "generator": "MinGW Makefiles",
    "cacheVariables":
    {
        "CMAKE_C_COMPILER": "C:/msys64/ucrt64/bin/gcc.exe",
        "CMAKE_CXX_COMPILER": "C:/msys64/ucrt64/bin/g++.exe",
        "CMAKE_MAKE_PROGRAM": "C:/msys64/ucrt64/bin/mingw32-make.exe"
    }
}
```

Note that this is not the complete JSON script for `CMakeUserPresets.json`. For
the full script, simply copy or duplicate the contents in `CMakePresets.json`
and replace the JSON objects under `configurePresets` with the one provided
above. Change the parameters in the template as you see fit (for example, define
your own `generator` if you used other than `MinGW Makefiles`, or specify the
path to your C++ compiler).

Here are some of the common build commands for use at the terminal:

```bash
cmake --build build --target clean_install
cmake --build build --target clean_full
cmake --build build --target clean_full_dependency
cmake --fresh --preset user_debug .
cmake --build build/debug
cmake --install build/debug
```

## Documentation Generation

This project uses Doxygen to generate code documentation. The terminal command
below is executed to generate the documentation:

```bash
doxygen Doxyfile
```

The `./docs/doxygen` directory will then be produced and modified at this project's source
directory. Doxygen provides different forms of output to view the documentation.
For this project, a simple static HTML page will suffice and can be accessed
under:

```bash
./docs/doxygen/html/index.html
```
