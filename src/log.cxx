#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace JAGE
{
    void LogInit()
    {
        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");

        AppLogger::Init(spdlog::level::trace);
        EngineLogger::Init(spdlog::level::trace);

        JAGE_MSG_TRACE("Initialised logger for engine.");
        APP_MSG_TRACE("Initialised logger for application.");
    }

    void LogDestroy() { spdlog::shutdown(); }

    void AppLogger::Init(spdlog::level::level_enum app_level)
    {
        logger = spdlog::stdout_color_st("APP");

        #ifdef DEBUG
        logger->set_level(app_level);
        #else
        logger->set_level(spdlog::level::critical);
        #endif
    }

    void EngineLogger::Init(spdlog::level::level_enum engine_level)
    {
        logger = spdlog::stdout_color_st("ENGINE");

        #ifdef DEBUG
        logger->set_level(engine_level);
        #else
        logger->set_level(spdlog::level::critical);
        #endif
    }
}
