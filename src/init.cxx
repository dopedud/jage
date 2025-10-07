#include "JAGE/core.h"
#include "log.h"

#include <argparse/argparse.hpp>

namespace JAGE
{
    void Init(int argc, char** argv)
    {
        // TODO: use a commnad-line parser library to parse command-line arguments

        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");

        // TODO: set log level based on command-line arguments
        AppLogger::Init(spdlog::level::trace);
        EngineLogger::Init(spdlog::level::trace);

        JAGE_MSG_TRACE("Initialised logger for engine.");
        APP_MSG_TRACE("Initialised logger for application.");
    }
}
