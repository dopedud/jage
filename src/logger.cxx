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

    void Logger::EngineLog_Info(std::string_view msg) { p_impl->enginelog->info(msg); }
    void Logger::EngineLog_Debug(std::string_view msg) { p_impl->enginelog->debug(msg); }
    void Logger::EngineLog_Warning(std::string_view msg) { p_impl->enginelog->warn(msg); }
    void Logger::EngineLog_Error(std::string_view msg) { p_impl->enginelog->error(msg); }

    void Logger::SandboxLog_Info(std::string_view msg) { p_impl->sandboxlog->info(msg); }
    void Logger::SandboxLog_Debug(std::string_view msg) { p_impl->sandboxlog->debug(msg); }
    void Logger::SandboxLog_Warning(std::string_view msg) { p_impl->sandboxlog->warn(msg); }
    void Logger::SandboxLog_Error(std::string_view msg) { p_impl->sandboxlog->error(msg); }

    void Logger::EngineLog_Info(std::string_view fmt, std::string_view s1) { p_impl->enginelog->info(fmt, s1); }
    void Logger::EngineLog_Debug(std::string_view fmt, std::string_view s1) { p_impl->enginelog->debug(fmt, s1); }
    void Logger::EngineLog_Warning(std::string_view fmt, std::string_view s1) { p_impl->enginelog->warn(fmt, s1); }
    void Logger::EngineLog_Error(std::string_view fmt, std::string_view s1) { p_impl->enginelog->error(fmt, s1); }

    void Logger::SandboxLog_Info(std::string_view fmt, std::string_view s1) { p_impl->sandboxlog->info(fmt, s1); }
    void Logger::SandboxLog_Debug(std::string_view fmt, std::string_view s1) { p_impl->sandboxlog->debug(fmt, s1); }
    void Logger::SandboxLog_Warning(std::string_view fmt, std::string_view s1) { p_impl->sandboxlog->warn(fmt, s1); }
    void Logger::SandboxLog_Error(std::string_view fmt, std::string_view s1) { p_impl->sandboxlog->error(fmt, s1); }
}
