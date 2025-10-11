# JAGE (Just Another Game Engine) - Game Engine from Scratch

## About

This repository is a project about making a game engine from scratch.

## Key Features

This engine focuses on exposing as much game development tools as possible to the end user, while abstracting away
low-level implementations and maintain extensibility as much as possible.

## Documentation Generation

This project uses Doxygen to generate code documentation. The terminal command below is executed to generate the
documentation:

```bash
doxygen Doxyfile
```

The `docs` directory will then be produced and modified at this project's source directory. Doxygen provides different
forms of output to view the documentation. For this project, a simple static HTML page will suffice and can be accessed
under:

```bash
docs/html/index.html
```

## Developer Notes

### Tech Stack

- **Programming Languages:** C, C++
- **Build System:** CMake
- **Rendering:** OpenGL
- **Game GUI:** TBA
- **Editor GUI:** Dear ImGui
- **Code Documentation:** Doxygen

## Compilation Notes

This project uses CMake to build, which requires the use of `CMakePresets.json` and `CMakeUserPresets.json` file. The
`CMakePresets.json` defines the general CMake configurations and is needed so that `CMakeUserPresets.json` can derive
its configurations from it. The `CMakeUserPresets.json` is a file that contains developer-specific CMake
configurations, which means each developer who wishes to contribute should define their own `CMakeUserPresets.json`. A
template is provided as shown below:

```json
{
    "name": "user-debug",
    "inherits": "debug",
    "displayName": "Debug Config (User)",
    "generator": "MinGW Makefiles",
    "cacheVariables":
    {
        "CMAKE_C_COMPILER": "C:/msys64/ucrt64/bin/gcc.exe",
        "CMAKE_CXX_COMPILER": "C:/msys64/ucrt64/bin/g++.exe",
        "CMAKE_MAKE_PROGRAM": "C:/msys64/mingw64/bin/mingw32-make.exe"
    }
},

{
    "name": "user-release",
    "inherits": "release",
    "displayName": "Release Config (User)",
    "generator": "MinGW Makefiles",
    "cacheVariables":
    {
        "CMAKE_C_COMPILER": "C:/msys64/ucrt64/bin/gcc.exe",
        "CMAKE_CXX_COMPILER": "C:/msys64/ucrt64/bin/g++.exe",
        "CMAKE_MAKE_PROGRAM": "C:/msys64/mingw64/bin/mingw32-make.exe"
    }
}
```

Note that this is not the complete JSON script for `CMakeUserPresets.json`. For the full script, simply copy or
duplicate the contents in `CMakePresets.json` and replace the JSON objects under `configurePresets` with the one
provided above. Change the parameters in the template as you see fit (for example, define your own `generator` if you
used other than `MinGW Makefiles`, or specify the path to your C/C++ compiler).

---

Here are some of the common build commands for use in terminal:

```bash
cmake --build build --target clean_install
cmake --build build --target clean_full
cmake --build build --target clean_full_dependency
cmake --fresh --preset user-debug .
cmake --build build/debug
cmake --install build/debug
```
