#include "time.h"

#include "log.h"

namespace JAGE
{
    namespace Time
    {
        using namespace std::chrono;

        static time_point<high_resolution_clock> start { high_resolution_clock::now() };

        static time_point<high_resolution_clock> current {};
        static time_point<high_resolution_clock> previous {};
        static duration<uint64_t, std::nano> deltatime {};
        static duration<uint64_t, std::nano> target_deltatime {};
        static bool target_fps_set {};

        void FrameLap()
        {
            current = high_resolution_clock::now();
            deltatime = duration_cast<nanoseconds>(current - previous);
            previous = current;

            if (target_fps_set && deltatime < target_deltatime)
            {
                deltatime = target_deltatime - deltatime;
                std::this_thread::sleep_for(deltatime);
            }
        }

        void SetTargetFPS(unsigned fps)
        {
            JAGE_LOG_INFO("frame rate capped to {} FPS", fps);
            target_deltatime = duration<uint64_t, std::nano>{ SECONDS_TO_NANO / fps };
            target_fps_set = true;
        }

        void UncapFPS() { target_fps_set = false; }

        float ElapsedTime()
        {
            time_point<high_resolution_clock> current { high_resolution_clock::now() };
            duration<uint64_t, std::nano> diff { current - start };

            return static_cast<float>(diff.count()) / static_cast<float>(MILLI_TO_NANO);
        }

        float DeltaTime() { return static_cast<float>(deltatime.count()) / static_cast<float>(MILLI_TO_NANO); }
    }
}