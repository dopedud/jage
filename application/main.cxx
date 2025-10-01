#include "JAGE/core.h"

int main(int argc, char** argv)
{
    using namespace JAGE;

    JAGE::Init(argc, argv);

    APP_MSG_INFO("Creating a window.");
    std::unique_ptr<Window> window = std::make_unique<Window>();

    APP_MSG_INFO("Setting event callback for window.");
    window->set_eventcallback([](Event& e) -> void
    {
        APP_LOG_INFO("{}", e.to_string());
    });

    while (true)
    {
        window->OnUpdate();
    }

    return 0;
}
