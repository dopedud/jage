#include <iostream>

#include "JAGE/core.h"

// int main(int argc, char** argv) <--- WE'LL USE THIS FOR LATER
int main()
{
    JAGE::Logger::Init();

    JAGE_MSG_INFO("Hey Engine World!");
    SANDBOX_LOG_INFO("Hey {}!", "Sandbox World");

    return 0;
}
