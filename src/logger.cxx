#include "logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace JAGE
{
    std::unique_ptr<Logger::Logger_PImpl> Logger::p_impl = nullptr;

    std::shared_ptr<spdlog::logger> Logger::Logger_PImpl::enginelog = nullptr;
    std::shared_ptr<spdlog::logger> Logger::Logger_PImpl::sandboxlog = nullptr;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T][%n] :- %v%$");

        Logger::p_impl = std::make_unique<Logger_PImpl>();
        
        p_impl->enginelog = spdlog::stdout_color_mt("ENGINE");
        p_impl->enginelog->set_level(spdlog::level::trace);

        p_impl->sandboxlog = spdlog::stdout_color_mt("SANDBOX");
        p_impl->sandboxlog->set_level(spdlog::level::trace);
    }
}
