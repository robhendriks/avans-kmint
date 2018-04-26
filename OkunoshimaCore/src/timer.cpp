#include "timer.h"

namespace okunoshima
{
    void timer::start()
    {
        m_started = true;
        m_paused = false;
        
        m_started_ticks = SDL_GetTicks();
        m_paused_ticks = 0;
    }
    
    void timer::stop()
    {
        m_started = m_paused = false;
        m_started_ticks = m_paused_ticks = 0;
    }
    
    void timer::pause()
    {
        if (m_started && !m_paused) {
            m_paused = true;
            m_paused_ticks = SDL_GetTicks() - m_started_ticks;
            m_started_ticks = 0;
        }
    }
    
    void timer::resume()
    {
        if (m_started && m_paused) {
            m_paused = false;
            m_started_ticks = SDL_GetTicks() - m_paused_ticks;
            m_paused_ticks = 0;
        }
    }
    
    uint32_t timer::get_ticks() const
    {
        if (m_started) {
            return m_paused ? m_paused_ticks : SDL_GetTicks() - m_started_ticks;
        }
        return 0;
    }
}
