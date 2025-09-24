#include "JAGE/core.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace JAGE
{
    void Logger::Init(
        spdlog::level::level_enum engine_level,
        spdlog::level::level_enum app_level
    )
    {
        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");
        
        enginelog = spdlog::stdout_color_mt("ENGINE");
        enginelog->set_level(engine_level);

        applog = spdlog::stdout_color_mt("APP");
        applog->set_level(app_level);
    }
}
