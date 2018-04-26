#include "genetic_entity.h"

namespace okunoshima
{
    void genetic_entity::init()
    {
        m_alive_timer.start();
    }
    
    void genetic_entity::print() const
    {
        std::cout << (*this) << std::endl;
    }
    
    void genetic_entity::kill()
    {
        if (!m_alive) { return; }
        
        m_alive = false;
        m_alive_ticks = m_alive_timer.get_ticks();
        m_alive_timer.stop();
    }
}
