#include "interval_timer.h"

namespace okunoshima
{
    void interval_timer::update()
    {
        if (!m_timer.is_started()) { m_timer.start(); }
        
        if (m_timer.get_ticks() >= m_interval) {
            m_timer.stop();
            
            m_callback();
            
            m_timer.start();
        }
    }
}
