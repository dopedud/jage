#pragma once

#include <memory>
#include <string_view>

#include "JAGE_export.h"

namespace JAGE
{
    class JAGE_API Logger
    {
    public:
        static void Init();

        static void EngineLog_Info(std::string_view msg);
        static void EngineLog_Debug(std::string_view msg);
        static void EngineLog_Warning(std::string_view msg);
        static void EngineLog_Error(std::string_view msg);

        static void SandboxLog_Info(std::string_view msg);
        static void SandboxLog_Debug(std::string_view msg);
        static void SandboxLog_Warning(std::string_view msg);
        static void SandboxLog_Error(std::string_view msg);

        static void EngineLog_Info(std::string_view fmt, std::string_view s1);
        static void EngineLog_Debug(std::string_view fmt, std::string_view s1);
        static void EngineLog_Warning(std::string_view fmt, std::string_view s1);
        static void EngineLog_Error(std::string_view fmt, std::string_view s1);

        static void SandboxLog_Info(std::string_view fmt, std::string_view s1);
        static void SandboxLog_Debug(std::string_view fmt, std::string_view s1);
        static void SandboxLog_Warning(std::string_view fmt, std::string_view s1);
        static void SandboxLog_Error(std::string_view fmt, std::string_view s1);
    private:
        struct JAGE_API Logger_PImpl;
        static std::unique_ptr<Logger_PImpl> p_impl;
    };

    #define JAGE_MSG_INFO(MSG) JAGE::Logger::EngineLog_Info(MSG)
    #define JAGE_MSG_DEBUG(MSG) JAGE::Logger::EngineLog_Debug(MSG)
    #define JAGE_MSG_WARNING(MSG) JAGE::Logger::EngineLog_Warning(MSG)
    #define JAGE_MSG_ERROR(MSG) JAGE::Logger::EngineLog_Error(MSG)
    
    #define SANDBOX_MSG_INFO(MSG) JAGE::Logger::SandboxLog_Info(MSG)
    #define SANDBOX_MSG_DEBUG(MSG) JAGE::Logger::SandboxLog_Debug(MSG)
    #define SANDBOX_MSG_WARNING(MSG) JAGE::Logger::SandboxLog_Warning(MSG)
    #define SANDBOX_MSG_ERROR(MSG) JAGE::Logger::SandboxLog_Error(MSG)

    #define JAGE_LOG1_INFO(FMT, S1) JAGE::Logger::EngineLog_Info(FMT, S1)
    #define JAGE_LOG1_DEBUG(FMT, S1) JAGE::Logger::EngineLog_Debug(FMT, S1)
    #define JAGE_LOG1_WARNING(FMT, S1) JAGE::Logger::EngineLog_Warning(FMT, S1)
    #define JAGE_LOG1_ERROR(FMT, S1) JAGE::Logger::EngineLog_Error(FMT, S1)

    #define SANDBOX_LOG1_INFO(FMT, S1) JAGE::Logger::SandboxLog_Info(FMT, S1)
    #define SANDBOX_LOG1_DEBUG(FMT, S1) JAGE::Logger::SandboxLog_Debug(FMT, S1)
    #define SANDBOX_LOG1_WARNING(FMT, S1) JAGE::Logger::SandboxLog_Warning(FMT, S1)
    #define SANDBOX_LOG1_ERROR(FMT, S1) JAGE::Logger::SandboxLog_Error(FMT, S1)
}
