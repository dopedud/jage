#pragma once

#include "jgpch.h"

#include "spdlog/spdlog.h"

#define JAGE_MSG_TRACE(MSG) JAGE::EngineLogger::EngineLog_Trace(MSG)
#define JAGE_MSG_DEBUG(MSG) JAGE::EngineLogger::EngineLog_Debug(MSG)
#define JAGE_MSG_INFO(MSG) JAGE::EngineLogger::EngineLog_Info(MSG)
#define JAGE_MSG_WARN(MSG) JAGE::EngineLogger::EngineLog_Warn(MSG)
#define JAGE_MSG_ERROR(MSG) JAGE::EngineLogger::EngineLog_Error(MSG)

#define JAGE_LOG_TRACE(LOG, ...) JAGE::EngineLogger::EngineLog_Trace(LOG, __VA_ARGS__)
#define JAGE_LOG_DEBUG(LOG, ...) JAGE::EngineLogger::EngineLog_Debug(LOG, __VA_ARGS__)
#define JAGE_LOG_INFO(LOG, ...) JAGE::EngineLogger::EngineLog_Info(LOG, __VA_ARGS__)
#define JAGE_LOG_WARN(LOG, ...) JAGE::EngineLogger::EngineLog_Warn(LOG, __VA_ARGS__)
#define JAGE_LOG_ERROR(LOG, ...) JAGE::EngineLogger::EngineLog_Error(LOG, __VA_ARGS__)

#ifdef JAGE_ENABLE_ASSERTS
#   define JAGE_CORE_ASSERT(x, message) \
    if (!(x)) { JAGE_LOG_ERROR("Assertion failed: {}", message); }
#   define JAGE_CORE_ASSERT_CALLBACK(x, callback, message) \
    if (!(x)) { JAGE_LOG_ERROR("Assertion failed: {}", message); callback; }
#else
#   define JAGE_CORE_ASSERT(x, message)
#   define JAGE_CORE_ASSERT_CALLBACK(x, callback, ...)
#endif

namespace JAGE
{
    class EngineLogger
    {
    private:
        inline static std::shared_ptr<spdlog::logger> enginelog = nullptr;
    public:
        static void Init(spdlog::level::level_enum engine_level);

        inline static void EngineLog_Trace(std::string_view msg) { enginelog->trace(msg); }
        inline static void EngineLog_Debug(std::string_view msg) { enginelog->debug(msg); }
        inline static void EngineLog_Info(std::string_view msg) { enginelog->info(msg); }
        inline static void EngineLog_Warn(std::string_view msg) { enginelog->warn(msg); }
        inline static void EngineLog_Error(std::string_view msg) { enginelog->error(msg); }

        template<typename... Args>
        inline static void EngineLog_Trace(std::string_view log, Args &&... args)
        { enginelog->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Debug(std::string_view log, Args &&... args)
        { enginelog->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Info(std::string_view log, Args &&... args)
        { enginelog->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Warn(std::string_view log, Args &&... args)
        { enginelog->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void EngineLog_Error(std::string_view log, Args &&... args)
        { enginelog->error(log, std::forward<Args>(args)...); }
    };
}