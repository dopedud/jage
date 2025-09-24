#pragma once

/**
 * @file core.h
 * @brief The Core header file that contains the core subsystems and utilities for JAGE.
 */

#include "jgpch.h"

#include "spdlog/spdlog.h"

#include "api_export.h"

namespace JAGE
{
    /**
     * @class Logger
     * @brief The Logger class used for logging JAGE and the game.
     * 
     * This Logger class uses @c spdlog as its logging backend. However, it is exposed to the end-user (i.e. the game),
     * effectively making JAGE and the game depend on @c spdlog to log. This tightly-coupled dependency should pose no
     * issues since logging rarely requires the developer to switch between different backends (compared to something
     * like a physics engine where a developer might use different ones for different scenarios).
     * 
     * The reason for the tightly-coupled dependency is because @c spdlog uses variadic templates internally to enable
     * variable number and types of objects to log. By defnition, templates should have its implementation exposed, so
     * both JAGE and the game should know what @c spdlog is.
     * 
     * It is possible to have only the JAGE know what logging backend it's using, and let the game use logging
     * from the JAGE without knowing what's going on internally by using the @c PImpl (pointer-to-implementation)
     * pattern. However, some sacrifices need to be made for templates and the @c PImpl pattern to work together.
     * Templates must be explicitly instantiated in the translation unit for types that a developer wants to support.
     * However, doing this would defeat the whole purpose of templates, which is to allow the flexibility of supporting
     * any type and any number of them. In fact, it is better to just overload the same function with different types
     * and amount of arguments a developer wants to support, since the intent is clearer.
     * 
     * Templates and the @c PImpl pattern are programming patterns that go against each other. Templates require the
     * implementation to be exposed, while the @c PImpl pattern requires it to be hidden. Templates are chose over the
     * @c PImpl pattern since the flexibility that comes with it is more important.
     */
    class JAGE_API Logger
    {
    private:
        inline static std::shared_ptr<spdlog::logger> enginelog = nullptr;
        inline static std::shared_ptr<spdlog::logger> applog = nullptr;
    public:
        static void Init(spdlog::level::level_enum engine_level, spdlog::level::level_enum app_level);

        inline static void EngineLog_Trace(std::string_view msg) { enginelog->trace(msg); }
        inline static void EngineLog_Debug(std::string_view msg) { enginelog->debug(msg); }
        inline static void EngineLog_Info(std::string_view msg) { enginelog->info(msg); }
        inline static void EngineLog_Warn(std::string_view msg) { enginelog->warn(msg); }
        inline static void EngineLog_Error(std::string_view msg) { enginelog->error(msg); }

        inline static void AppLog_Trace(std::string_view msg) { applog->trace(msg); }
        inline static void AppLog_Debug(std::string_view msg) { applog->debug(msg); }
        inline static void AppLog_Info(std::string_view msg) { applog->info(msg); }
        inline static void AppLog_Warn(std::string_view msg) { applog->warn(msg); }
        inline static void AppLog_Error(std::string_view msg) { applog->error(msg); }

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

        template<typename... Args>
        inline static void AppLog_Trace(std::string_view log, Args &&... args)
        { applog->trace(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Debug(std::string_view log, Args &&... args)
        { applog->debug(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Info(std::string_view log, Args &&... args)
        { applog->info(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Warn(std::string_view log, Args &&... args)
        { applog->warn(log, std::forward<Args>(args)...); }
        template<typename... Args>
        inline static void AppLog_Error(std::string_view log, Args &&... args)
        { applog->error(log, std::forward<Args>(args)...); }
    };

    #define JAGE_MSG_TRACE(MSG) JAGE::Logger::EngineLog_Trace(MSG)
    #define JAGE_MSG_DEBUG(MSG) JAGE::Logger::EngineLog_Debug(MSG)
    #define JAGE_MSG_INFO(MSG) JAGE::Logger::EngineLog_Info(MSG)
    #define JAGE_MSG_WARN(MSG) JAGE::Logger::EngineLog_Warn(MSG)
    #define JAGE_MSG_ERROR(MSG) JAGE::Logger::EngineLog_Error(MSG)

    #define APP_MSG_TRACE(MSG) JAGE::Logger::AppLog_Trace(MSG)
    #define APP_MSG_DEBUG(MSG) JAGE::Logger::AppLog_Debug(MSG)
    #define APP_MSG_INFO(MSG) JAGE::Logger::AppLog_Info(MSG)
    #define APP_MSG_WARN(MSG) JAGE::Logger::AppLog_Warn(MSG)
    #define APP_MSG_ERROR(MSG) JAGE::Logger::AppLog_Error(MSG)

    #define JAGE_LOG_TRACE(LOG, ...) JAGE::Logger::EngineLog_Trace(LOG, __VA_ARGS__)
    #define JAGE_LOG_DEBUG(LOG, ...) JAGE::Logger::EngineLog_Debug(LOG, __VA_ARGS__)
    #define JAGE_LOG_INFO(LOG, ...) JAGE::Logger::EngineLog_Info(LOG, __VA_ARGS__)
    #define JAGE_LOG_WARN(LOG, ...) JAGE::Logger::EngineLog_Warn(LOG, __VA_ARGS__)
    #define JAGE_LOG_ERROR(LOG, ...) JAGE::Logger::EngineLog_Error(LOG, __VA_ARGS__)

    #define APP_LOG_TRACE(LOG, ...) JAGE::Logger::AppLog_Trace(LOG, __VA_ARGS__)
    #define APP_LOG_DEBUG(LOG, ...) JAGE::Logger::AppLog_Debug(LOG, __VA_ARGS__)
    #define APP_LOG_INFO(LOG, ...) JAGE::Logger::AppLog_Info(LOG, __VA_ARGS__)
    #define APP_LOG_WARN(LOG, ...) JAGE::Logger::AppLog_Warn(LOG, __VA_ARGS__)
    #define APP_LOG_ERROR(LOG, ...) JAGE::Logger::AppLog_Error(LOG, __VA_ARGS__)
}
