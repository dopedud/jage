#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    /**
     * @class WindowBackend class
     * @brief The WindowBackend class that act as an abstraction to window backends.
     *
     * NOTE: This class should have the same states and behaviours as the Window class in @c core.h (meaning the same
     * set of functions and variables, except the fact that WindowBackend has purely virtual functions, but that's
     * because of its abstraction nature).
     */
    class WindowBackend
    {
    public:
        virtual ~WindowBackend() = default;

        virtual unsigned int width() const = 0;
        virtual unsigned int height() const = 0;

        virtual void OnUpdate() = 0;

        virtual void set_eventcallback(const EventCallbackFn& callback) = 0;
        virtual void set_vsync(bool enabled) = 0;
        virtual bool is_vsync() const = 0;
    protected:
        WindowProperties properties;
        EventCallbackFn callback;
    };

    /**
     * @class Window_Impl class
     * @brief The Window_Impl class that implements Window class.
     * 
     * NOTE: This class should have the same states and behaviours as the Window class in @c core.h (meaning the same
     * set of functions and variables).
     */
    class Window::Window_Impl
    {
    public:
        Window_Impl(const WindowProperties& properties = WindowProperties{});

        inline unsigned int width() const { return backend->width(); }
        inline unsigned int height() const { return backend->height(); }

        inline void OnUpdate() { backend->OnUpdate(); }

        inline void set_eventcallback(const EventCallbackFn& callback) { backend->set_eventcallback(callback); }
        inline void set_vsync(bool enabled) { backend->set_vsync(enabled); }
        inline bool is_vsync() const { return backend->is_vsync(); }
    private:
        std::unique_ptr<WindowBackend> backend;
    };
}
