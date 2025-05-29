/*******************************************************************************
    This file is part of ColPack, which is under its License protection.
    You should have received a copy of the License. If not, see 
    <https://github.com/CSCsw/ColPack>
*******************************************************************************/

#include "Timer.h"
#include <chrono>

namespace ColPack
{
    // Constructor
    Timer::Timer() : running(false) {}

    // Start the timer
    void Timer::Start()
    {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }

    // Stop the timer
    void Timer::Stop()
    {
        end_time = std::chrono::high_resolution_clock::now();
        running = false;
    }

    // Get elapsed wall time in seconds
    double Timer::GetWallTime()
    {
        if (running)
        {
            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double>(now - start_time).count();
        }
        return std::chrono::duration<double>(end_time - start_time).count();
    }
}
