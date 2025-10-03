#include "JAGE/core.h"
#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace JAGE
{
    void AppLogger::Init(spdlog::level::level_enum app_level)
    {
        logger = spdlog::stdout_color_mt("APP");

#ifdef DEBUG
        logger->set_level(app_level);
#else
        logger->set_level(spdlog::level::off);
#endif
    }

    void EngineLogger::Init(spdlog::level::level_enum engine_level)
    {
        logger = spdlog::stdout_color_mt("ENGINE");

#ifdef DEBUG
        logger->set_level(engine_level);
#else
        logger->set_level(spdlog::level::off);
#endif
    }
}