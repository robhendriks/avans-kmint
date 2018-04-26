#ifndef interval_timer_h
#define interval_timer_h

#include <functional>
#include "timer.h"

namespace okunoshima
{
    using interval_timer_callback = std::function<void()>;
    
    class interval_timer
    {
        timer m_timer;
        int m_interval;
        interval_timer_callback m_callback;
    public:
        interval_timer(int interval) : m_interval{interval}, m_callback{nullptr} {}
        void update();
        
        void set_callback(interval_timer_callback&& callback) { m_callback = callback; }
    };
}

#endif
