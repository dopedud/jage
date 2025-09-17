#pragma once

#include <memory>

#include "engine_export.h"

namespace JAGE
{
    class JAGE_EXPORT Logger
    {
    private:
        struct JAGE_EXPORT Logger_PImpl;
        static std::unique_ptr<Logger_PImpl> p_impl;
    public:
        static void Init();

        static void EngineLog_Info(const char* fmt)
        {
        }

        static void SandboxLog_Info(const char* fmt)
        {
        }
    };

    #define JAGE_MSG_INFO(MSG) JAGE::Logger::EngineLog_Info(MSG)
    #define JAGE_LOG_INFO(...) JAGE::Logger::EngineLog_Info(__VA_ARGS__)

    #define SANDBOX_MSG_INFO(MSG) JAGE::Logger::SandboxLog_Info(MSG)
    #define SANDBOX_LOG_INFO(...) JAGE::Logger::SandboxLog_Info(__VA_ARGS__)
}
