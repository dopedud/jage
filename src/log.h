#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"

namespace JAGE
{
    void LogInit();
    void LogDestroy();

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
        inline static std::shared_ptr<spdlog::logger> logger { nullptr };
    public:
        static void Init(spdlog::level::level_enum engine_level);

        inline static void Trace(std::string_view msg)      { logger->trace(msg); }
        inline static void Debug(std::string_view msg)      { logger->debug(msg); }
        inline static void Info(std::string_view msg)       { logger->info(msg); }
        inline static void Warn(std::string_view msg)       { logger->warn(msg); }
        inline static void Error(std::string_view msg)      { logger->error(msg); }
        inline static void Critical(std::string_view msg)   { logger->critical(msg); }

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
        template<typename... Args>
        inline static void Critical(std::string_view log, Args &&... args)
        { logger->critical(log, std::forward<Args>(args)...); }
    };

    #define JAGE_MSG_TRACE(MSG)     JAGE::EngineLogger::Trace(MSG)
    #define JAGE_MSG_DEBUG(MSG)     JAGE::EngineLogger::Debug(MSG)
    #define JAGE_MSG_INFO(MSG)      JAGE::EngineLogger::Info(MSG)
    #define JAGE_MSG_WARN(MSG)      JAGE::EngineLogger::Warn(MSG)
    #define JAGE_MSG_ERROR(MSG)     JAGE::EngineLogger::Error(MSG)
    #define JAGE_MSG_CRITICAL(MSG)  JAGE::EngineLogger::Critical(MSG); std::abort()

    #define JAGE_LOG_TRACE(LOG, ...)        JAGE::EngineLogger::Trace(LOG, __VA_ARGS__)
    #define JAGE_LOG_DEBUG(LOG, ...)        JAGE::EngineLogger::Debug(LOG, __VA_ARGS__)
    #define JAGE_LOG_INFO(LOG, ...)         JAGE::EngineLogger::Info(LOG, __VA_ARGS__)
    #define JAGE_LOG_WARN(LOG, ...)         JAGE::EngineLogger::Warn(LOG, __VA_ARGS__)
    #define JAGE_LOG_ERROR(LOG, ...)        JAGE::EngineLogger::Error(LOG, __VA_ARGS__)
    #define JAGE_LOG_CRITICAL(LOG, ...)     JAGE::EngineLogger::Critical(LOG, __VA_ARGS__); std::abort()

    #ifdef JAGE_ENABLE_ASSERTS
    #   define JAGE_MSG_ASSERT(X, MSG) if (!(X)) { JAGE_MSG_CRITICAL(MSG); }
    #   define JAGE_LOG_ASSERT(X, LOG, ...) if (!(X)) { JAGE_LOG_CRITICAL(LOG, __VA_ARGS__); }
    #else
    #   define JAGE_MSG_ASSERT(X, MSG)
    #   define JAGE_LOG_ASSERT(X, LOG, ...)
    #endif
}

template <>
struct fmt::formatter<glm::vec3>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const glm::vec3& v, FormatContext& ctx) const
    {
        return fmt::format_to
        (
            ctx.out(),
            "[{: .6f}, {: .6f}, {: .6f}]",
            v.x, v.y, v.z
        );
    }
};

template <>
struct fmt::formatter<glm::mat4>
{
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const glm::mat4& m, FormatContext& ctx) const
    {
        auto out { ctx.out() };

        fmt::format_to(out, "\n[\n");
        for (int row = 0; row < 4; row++)
        {
            fmt::format_to
            (
                out,
                "    [{: .6f}, {: .6f}, {: .6f}, {: .6f}]{}\n",
                m[row][0], m[row][1], m[row][2], m[row][3],
                row < 3 ? "," : ""
            );
        }
        fmt::format_to(out, "]");

        return out;
    }
};