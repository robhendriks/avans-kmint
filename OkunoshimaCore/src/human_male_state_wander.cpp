#include "human_male_state_wander.h"
#include "human_male_state_take_picture.h"

namespace okunoshima
{
    void human_male_state_wander::enter()
    {
        m_timer.start();
    }
    
    void human_male_state_wander::check_state()
    {
        if (m_timer.get_ticks() >= 20000) {
            m_timer.stop();
            
            m_human.set_state(std::make_shared<human_male_state_take_picture>(m_human));
        }
    }
    
    void human_male_state_wander::update()
    {
        m_human.wander();
    }
    
    void human_male_state_wander::draw(graphics& g)
    {
    }
}
