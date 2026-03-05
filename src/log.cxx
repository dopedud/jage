#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace JAGE
{
    void LogInit()
    {
        spdlog::set_pattern("%^[%Y/%m/%d | %T][%n][%L] :- %v%$");

        AppLogger::Init(spdlog::level::trace);
        EngineLogger::Init(spdlog::level::trace);

        JAGE_MSG_TRACE("Initialised logger for engine.");
        APP_MSG_TRACE("Initialised logger for application.");
    }

    void LogDestroy() { spdlog::shutdown(); }

    void AppLogger::Init(spdlog::level::level_enum app_level)
    {
        logger = spdlog::stdout_color_st("APP");

        #ifdef DEBUG
        logger->set_level(app_level);
        #else
        logger->set_level(spdlog::level::critical);
        #endif
    }

    void EngineLogger::Init(spdlog::level::level_enum engine_level)
    {
        logger = spdlog::stdout_color_st("ENGINE");

        #ifdef DEBUG
        logger->set_level(engine_level);
        #else
        logger->set_level(spdlog::level::critical);
        #endif
    }
}

template <>
struct fmt::formatter<glm::vec3>
{
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const glm::vec3 &v, FormatContext &ctx) const
    {
        return fmt::format_to(
            ctx.out(),
            "[{: .6f}, {: .6f}, {: .6f}]",
            v.x, v.y, v.z);
    }
};

template <>
struct fmt::formatter<glm::mat4>
{
    constexpr auto parse(fmt::format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const glm::mat4 &m, FormatContext &ctx) const
    {
        auto out{ctx.out()};

        fmt::format_to(out, "\n[\n");
        for (int row = 0; row < 4; row++)
        {
            fmt::format_to(
                out,
                "    [{: .6f}, {: .6f}, {: .6f}, {: .6f}]{}\n",
                m[row][0], m[row][1], m[row][2], m[row][3],
                row < 3 ? "," : "");
        }
        fmt::format_to(out, "]");

        return out;
    }
};
