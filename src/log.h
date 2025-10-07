#pragma once

#include "jgpch.h"
#include "JAGE/core.h"

#include "spdlog/spdlog.h"

#define JAGE_MSG_TRACE(MSG) JAGE::EngineLogger::Trace(MSG)
#define JAGE_MSG_DEBUG(MSG) JAGE::EngineLogger::Debug(MSG)
#define JAGE_MSG_INFO(MSG) JAGE::EngineLogger::Info(MSG)
#define JAGE_MSG_WARN(MSG) JAGE::EngineLogger::Warn(MSG)
#define JAGE_MSG_ERROR(MSG) JAGE::EngineLogger::Error(MSG)

#define JAGE_LOG_TRACE(LOG, ...) JAGE::EngineLogger::Trace(LOG, __VA_ARGS__)
#define JAGE_LOG_DEBUG(LOG, ...) JAGE::EngineLogger::Debug(LOG, __VA_ARGS__)
#define JAGE_LOG_INFO(LOG, ...) JAGE::EngineLogger::Info(LOG, __VA_ARGS__)
#define JAGE_LOG_WARN(LOG, ...) JAGE::EngineLogger::Warn(LOG, __VA_ARGS__)
#define JAGE_LOG_ERROR(LOG, ...) JAGE::EngineLogger::Error(LOG, __VA_ARGS__)

#ifdef JAGE_ENABLE_ASSERTS
#   define JAGE_ASSERT(x, message) \
    if (!(x)) { JAGE_MSG_ERROR("Assertion failed: " + std::string{ message }); DEBUG_BREAK; }
#else
#   define JAGE_ASSERT(x, message)
#endif

namespace JAGE
{
    /**
     * @class EngineLogger
     * @brief The @c EngineLogger class used to log engine operations.
     * 
     * @c EngineLogger should have the same class structure as @c AppLogger (as in, having the same member variables and
     * member functions). The reason for this separation despite being the exact same class is to hide engine logging
     * from the game. The idea is that the game should only log game operations, and although the engine can log game
     * operations within its own, the engine should also only log its operations. This helps reinforce separation of
     * concerns and loose coupling between JAGE and the game.
     */
    class EngineLogger
    {
    private:
        inline static std::shared_ptr<spdlog::logger> logger = nullptr;
    public:
        static void Init(spdlog::level::level_enum engine_level);

        inline static void Trace(std::string_view msg) { logger->trace(msg); }
        inline static void Debug(std::string_view msg) { logger->debug(msg); }
        inline static void Info(std::string_view msg) { logger->info(msg); }
        inline static void Warn(std::string_view msg) { logger->warn(msg); }
        inline static void Error(std::string_view msg) { logger->error(msg); }

        template<typename... Args>
        inline static void Trace(std::string_view log, Args &&... args)
        { logger->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Debug(std::string_view log, Args &&... args)
        { logger->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Info(std::string_view log, Args &&... args)
        { logger->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Warn(std::string_view log, Args &&... args)
        { logger->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void Error(std::string_view log, Args &&... args)
        { logger->error(log, std::forward<Args>(args)...); }
    };
}