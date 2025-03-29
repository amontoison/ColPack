/*******************************************************************************
    This file is part of ColPack, which is under its License protection.
    You should have received a copy of the License. If not, see
    <https://github.com/CSCsw/ColPack>
*******************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace ColPack
{
    /** @ingroup group4
     *  @brief Timer class for performance measurements using std::chrono.
     *
     *  This class provides a precise timer based on std::chrono,
     *  suitable for benchmarking and low-latency measurements.
     */
    class Timer
    {
      private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        bool running;

      public:
        Timer();         // Constructor
        void Start();    // Start the timer
        void Stop();     // Stop the timer
        double GetWallTime(); // Get elapsed time in seconds
    };
}

#endif // TIMER_H
