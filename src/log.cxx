#include "JAGE/core.h"
#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace JAGE
{
    void AppLogger::Init(spdlog::level::level_enum app_level)
    {
        applog = spdlog::stdout_color_mt("APP");

#ifdef DEBUG
        applog->set_level(app_level);
#else
        applog->set_level(spdlog::level::off);
#endif
    }

    void EngineLogger::Init(spdlog::level::level_enum engine_level)
    {
        enginelog = spdlog::stdout_color_mt("ENGINE");

#ifdef DEBUG
        enginelog->set_level(engine_level);
#else
        enginelog->set_level(spdlog::level::off);
#endif
    }
}