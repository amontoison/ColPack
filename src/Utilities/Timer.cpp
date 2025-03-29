/*******************************************************************************
    This file is part of ColPack, which is under its License protection.
    You should have received a copy of the License. If not, see 
    <https://github.com/CSCsw/ColPack>
*******************************************************************************/

//using namespace std;

#include "Timer.h"

#include <chrono>

namespace ColPack
{
    class Timer
    {
      private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        bool running;

      public:
        // Constructor
        Timer() : running(false) {}

        // Start the timer
        void Start()
        {
            start_time = std::chrono::high_resolution_clock::now();
            running = true;
        }

        // Stop the timer
        void Stop()
        {
            end_time = std::chrono::high_resolution_clock::now();
            running = false;
        }

        // Get elapsed wall time in seconds
        double GetWallTime()
        {
            if (running)
            {
                auto now = std::chrono::high_resolution_clock::now();
                return std::chrono::duration<double>(now - start_time).count();
            }
            return std::chrono::duration<double>(end_time - start_time).count();
        }
    };
}
