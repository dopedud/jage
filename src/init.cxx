#include "JAGE/core.h"
#include "JAGE/assets.h"

#include "log.h"
#include "platform/platform.h"

namespace JAGE
{
    namespace fs = std::filesystem;

    void Init(int argc, char** argv)
    {
        fs::path exe_dir { fs::canonical(fs::path{ argv[0] }) };
        fs::path root_dir { exe_dir.parent_path().parent_path() };
        fs::current_path(root_dir);

        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");

        AppLogger::Init(spdlog::level::trace);
        EngineLogger::Init(spdlog::level::trace);

        JAGE_MSG_TRACE("Initialised logger for engine.");
        APP_MSG_TRACE("Initialised logger for application.");

        JAGE_LOG_INFO("Current working directory: {}", fs::current_path().string());

        AssetManager::instance().Initialise();

        glfwSetErrorCallback([](int error_code, const char* desc) -> void
        {
            JAGE_LOG_ERROR("GLFW error {}: {}.", error_code, desc);
        });

        int success { glfwInit() };
        JAGE_MSG_ASSERT(success, "GLFW error: Failed to initialise GLFW.")

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Destroy()
    {
        glfwTerminate();

        AssetManager::release();

        spdlog::shutdown();
    }
}