#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

/**
 * Timing utility for measuring perf
 */
using namespace std::chrono;

namespace yengine {

  typedef duration<long, std::ratio<1,60>> sixtieths_of_a_sec;

  class Timer
  {
  private:
    time_point<steady_clock> m_Last;
  public:
    Timer() : m_Last(steady_clock::now()) {}

    double getElapsedAndTick()
    {
      auto currentTime = steady_clock::now();
      duration<double, std::milli> elapsed = currentTime - m_Last;
      m_Last = currentTime;

      return elapsed.count();
    }

    void countFpsAndTick ()
    {
      auto currentTime = steady_clock::now();
      duration<double, std::milli> elapsed = currentTime - m_Last;
      m_Last = currentTime;

      std::cout << "FPS: " << (1000.0/elapsed.count()) << std::endl;
    }
  };

} // ns

#endif
