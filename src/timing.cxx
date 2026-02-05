#include "timing.h"

#include "log.h"

namespace JAGE
{
    namespace Time
    {
        using namespace std::chrono;

        static time_point<high_resolution_clock> start { high_resolution_clock::now() };

        static time_point<high_resolution_clock> current {};
        static time_point<high_resolution_clock> previous {};
        static duration<u64, std::nano> deltatime {};
        static duration<u64, std::nano> target_deltatime {};
        static bool target_fps_set {};

        void FrameLap()
        {
            current = high_resolution_clock::now();
            deltatime = duration_cast<nanoseconds>(current - previous);

            if (target_fps_set && deltatime < target_deltatime)
            {
                duration<u64, std::nano> remaining_deltatime { target_deltatime - deltatime };
                deltatime = target_deltatime;
                // std::this_thread::sleep_for(remaining_deltatime);

                while (high_resolution_clock::now() - previous < target_deltatime) {}
            }

            previous = high_resolution_clock::now();
        }

        void SetTargetFPS(unsigned fps)
        {
            target_deltatime = duration<u64, std::nano>{ SECONDS_TO_NANO / fps };
            target_fps_set = true;
            JAGE_LOG_INFO("frame rate capped to {} FPS.", fps);
        }

        void UncapFPS() { target_fps_set = false; }

        float ElapsedTime()
        {
            time_point<high_resolution_clock> current { high_resolution_clock::now() };
            duration<u64, std::nano> diff { current - start };

            return static_cast<float>(diff.count()) / static_cast<float>(MILLI_TO_NANO);
        }

        float DeltaTime() { return static_cast<float>(deltatime.count()) / static_cast<float>(MILLI_TO_NANO); }
    }
}