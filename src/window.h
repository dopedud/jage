#pragma once

#include "JAGE/core.h"

namespace JAGE
{
    /**
     * @class WindowBackend
     * @brief The @c WindowBackend class that act as an abstraction to window backends.
     *
     * This class should have the same states and behaviours as the @c Window class in @c core.h (meaning the same set
     * of functions and variables, except the fact that @c WindowBackend has purely virtual functions, which is because
     * of its abstraction nature).
     */
    class WindowBackend
    {
    public:
        virtual ~WindowBackend() = default;

        virtual unsigned int width() const = 0;
        virtual unsigned int height() const = 0;

        virtual void OnPollEvents() = 0;
        virtual void OnClear() = 0;
        virtual void OnRender() = 0;

        virtual void set_eventcallback(const EventCallbackFn& callback) = 0;
        virtual void set_vsync(bool enabled) = 0;
        virtual bool vsync() const = 0;

        virtual void* handle() = 0;
    protected:
        struct WindowData
        {
            WindowProperties properties;
            EventCallbackFn callback;
        };

        WindowData data;
    };

    /**
     * @class Window_Impl
     * @brief The @c Window_Impl class that implements Window class.
     * 
     * This class should have the same states and behaviours as the @c Window class in @c core.h (meaning the same set
     * of functions and variables).
     */
    class Window::Window_Impl
    {
    public:
        Window_Impl(const WindowProperties& properties = WindowProperties{});

        unsigned int width() const { return backend->width(); }
        unsigned int height() const { return backend->height(); }

        void OnPollEvents() { backend->OnPollEvents(); }
        void OnClear() { backend->OnClear(); }
        void OnRender() { backend->OnRender(); }

        void set_eventcallback(const EventCallbackFn& callback) { backend->set_eventcallback(callback); }
        void set_vsync(bool enabled) { backend->set_vsync(enabled); }
        bool vsync() const { return backend->vsync(); }

        void* handle() { return backend->handle(); }
    private:
        std::unique_ptr<WindowBackend> backend;
    };
}
