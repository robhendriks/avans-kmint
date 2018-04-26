#include "human_female_state_wait.h"
#include "human_female_state_wander.h"
#include "world.h"

namespace okunoshima
{
    void human_female_state_wait::check_state()
    {
        auto& em = m_human.get_world().get_entity_manager();
        
        if (!em.agents_in_radius(m_human, 30)) {
            m_human.set_state(std::make_shared<human_female_state_wander>(m_human));
        }
    }
    
    void human_female_state_wait::update()
    {
    }
    
    void human_female_state_wait::draw(graphics& g)
    {
    }
}
