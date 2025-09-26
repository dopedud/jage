#include "JAGE/core.h"

// int main(int argc, char** argv) <--- WE'LL USE THIS FOR LATER
int main()
{
    JAGE::Logger::Init(spdlog::level::trace, spdlog::level::trace);

    JAGE_MSG_INFO("Hey Engine World!");
    JAGE_MSG_TRACE("This is a trace message!");
    JAGE_MSG_DEBUG("This is a debug message!");
    JAGE_MSG_WARN("This is a warn message!");
    JAGE_MSG_ERROR("This is a error message!");
    APP_LOG_INFO("Hey {}!", "App World");

    std::unique_ptr<JAGE::Window> window = std::make_unique<JAGE::Window>(JAGE::Window::create());

    while (true)
    {
        window->OnUpdate();
    }

    return 0;
}
