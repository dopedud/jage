#include "JAGE/core.h"
#include "JAGE/resources.h"
#include "JAGE/math.h"

#include "log.h"

namespace JAGE
{
    namespace fs = std::filesystem;

    void Init(int argc, char** argv)
    {
        fs::path exe_dir { fs::path{ argv[0] } };
        fs::path root_dir { exe_dir.parent_path().parent_path() };
        fs::current_path(root_dir);

        LogInit();

        JAGE_LOG_INFO("Current working directory: {}", fs::current_path().string());

        ResourceManager::instance();
    }

    void Destroy()
    {
        LogDestroy();

        ResourceManager::reset();
    }
}