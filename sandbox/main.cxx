#include <iostream>

#include "engine.h"

// int main(int argc, char** argv) <--- WE'LL USE THIS FOR LATER
int main()
{
    JAGE::Logger::Init();

    JAGE_MSG_INFO("Hey World!");
    SANDBOX_LOG_INFO("Hey {}!", "World");

    return 0;
}
