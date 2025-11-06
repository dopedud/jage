#include "JAGE/core.h"
#include "JAGE/resources/core.h"

#include "log.h"

namespace JAGE
{
    void Init(int argc, char** argv)
    {
        auto exe_dir { std::filesystem::path(argv[0]).parent_path() };
        std::filesystem::current_path(exe_dir.parent_path());

        LogInit();

        JAGE_LOG_TRACE("Current working directory: {}", std::filesystem::current_path().string());

        ResourceManager::instance();
    }

    void Destroy()
    {
        ResourceManager::reset();
    }
}