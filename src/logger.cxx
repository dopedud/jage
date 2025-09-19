#include "JAGE/core.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace JAGE
{
    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T][%n] :- %v%$");
        
        enginelog = spdlog::stdout_color_mt("ENGINE");
        enginelog->set_level(spdlog::level::trace);

        sandboxlog = spdlog::stdout_color_mt("SANDBOX");
        sandboxlog->set_level(spdlog::level::trace);
    }
}
