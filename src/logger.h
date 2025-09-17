#pragma once

#include <memory>
#include <utility>

#include "engine.h"

#include "spdlog/spdlog.h"

namespace JAGE
{
    struct JAGE_EXPORT Logger::Logger_PImpl
    {
        static std::shared_ptr<spdlog::logger> enginelog;
        static std::shared_ptr<spdlog::logger> sandboxlog;
    };
}