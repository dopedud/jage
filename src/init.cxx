#include "JAGE/core.h"
#include "log.h"

namespace JAGE
{
    void Init(int argc, char** argv)
    {
        // TODO: use a commnad-line parser library to parse command-line arguments

        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");

        // TODO: set log level based on command-line arguments
        AppLogger::Init(spdlog::level::trace);
        EngineLogger::Init(spdlog::level::trace);

        JAGE_MSG_TRACE("Testing logging for engine.");
        JAGE_MSG_TRACE("Trace message.");
        JAGE_MSG_DEBUG("Debug message.");
        JAGE_MSG_INFO("Info message.");
        JAGE_MSG_WARN("Warn message.");
        JAGE_MSG_ERROR("Error message.");

        APP_MSG_TRACE("Testing logging for application.");
        APP_MSG_TRACE("Trace message.");
        APP_MSG_DEBUG("Debug message.");
        APP_MSG_INFO("Info message.");
        APP_MSG_WARN("Warn message.");
        APP_MSG_ERROR("Error message.");

        JAGE_MSG_INFO("Initialised logger for engine.");
        APP_MSG_INFO("Initialised logger for application.");
    }
}
