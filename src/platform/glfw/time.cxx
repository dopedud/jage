#include "JAGE/core.h"

#include "platform/platform.h"

namespace JAGE
{
    namespace Time
    {
        using namespace std::chrono;

        static time_point start { high_resolution_clock::now() };

        void StartLoop()
        {

        }

        void EndLoop()
        {

        }

        double ElapsedTime()
        {
            time_point current { high_resolution_clock::now() };
            duration<double, std::milli> diff { duration_cast<nanoseconds>(current - start) };

            return diff.count();

            // could just return current time reported from GLFW
            // return glfwGetTime();
        }
    }
}