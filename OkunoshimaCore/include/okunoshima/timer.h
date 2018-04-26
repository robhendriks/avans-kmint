#ifndef timer_h
#define timer_h

#include <SDL2/SDL.h>

namespace okunoshima
{
    class timer
    {
        bool m_started;
        bool m_paused;
        uint32_t m_started_ticks;
        uint32_t m_paused_ticks;
    public:
        timer() : m_started{false}, m_paused{false}, m_started_ticks{0}, m_paused_ticks{0} {}
        
        void start();
        void stop();
        void pause();
        void resume();
        
        uint32_t get_ticks() const;
        
        bool is_started() const { return m_started; }
        bool is_paused() const { return m_paused; };
    };
}

#endif
