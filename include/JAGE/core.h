#pragma once

/**
 * @file core.h
 * @brief The Core header file that contains the core subsystems and utilities for JAGE.
 */

#include <memory>
#include <string_view>
#include <utility>
#include <cstdint>

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
        inline static std::shared_ptr<spdlog::logger> sandboxlog = nullptr;
    public:
        static void Init();

        inline static void EngineLog_Info(std::string_view msg) { enginelog->info(msg); }
        inline static void SandboxLog_Info(std::string_view msg) { sandboxlog->info(msg); }

        template<typename... Args>
        inline static void EngineLog_Info(std::string_view log, Args &&... args)
        {
            enginelog->info(log, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void SandboxLog_Info(std::string_view log, Args &&... args)
        {
            sandboxlog->info(log, std::forward<Args>(args)...);
        }
    };

    #define JAGE_MSG_INFO(MSG) JAGE::Logger::EngineLog_Info(MSG)
    #define SANDBOX_MSG_INFO(MSG) JAGE::Logger::SandboxLog_Info(MSG)

    #define JAGE_LOG_INFO(LOG, ...) JAGE::Logger::EngineLog_Info(LOG, __VA_ARGS__)
    #define SANDBOX_LOG_INFO(LOG, ...) JAGE::Logger::SandboxLog_Info(LOG, __VA_ARGS__)

    enum class EventType : uint8_t
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowUnFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };   

    #define BIT(x) (1 << x)

    enum class EventCategory : uint8_t
    {
        None = 0,
        Application     = BIT(0),
        Input           = BIT(1),
        Keyboard        = BIT(2),
        Mouse           = BIT(3),
        MouseButton     = BIT(4)
    };

    class JAGE_API Event
    {
    public:
        virtual std::string_view name() const = 0;
        virtual EventType event_type() const = 0;
        virtual EventCategory event_category() const = 0;
        virtual std::string_view ToString() const { return name(); }

        inline bool is_category(EventCategory category) { return event_category() & category; }
    protected:
        bool handled = false;
    };
}
