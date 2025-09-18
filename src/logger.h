#pragma once

#include <memory>

#include "engine.h"

#include "spdlog/spdlog.h"

namespace JAGE
{
    struct JAGE_API Logger::Logger_PImpl
    {
        static std::shared_ptr<spdlog::logger> enginelog;
        static std::shared_ptr<spdlog::logger> sandboxlog;
    };
}
