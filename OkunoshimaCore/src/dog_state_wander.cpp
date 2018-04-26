#include "dog_state_wander.h"
#include "dog_state_find_human.h"
#include "dog_state_attack.h"
#include "world.h"

namespace okunoshima
{
    void dog_state_wander::check_state()
    {
        if (m_dog.get_thirst() >= MAX_THIRST) {
            m_dog.set_state(std::make_shared<dog_state_find_human>(m_dog));
        }
        
        auto& em = m_dog.get_world().get_entity_manager();
        auto target = em.nearest_agent_in_radius(m_dog, ATTACK_RADIUS);
        if (target) {
            m_dog.set_state(std::make_shared<dog_state_attack>(m_dog, target));
        }
    }
    
    void dog_state_wander::update()
    {
        m_dog.wander();
    }
    
    void dog_state_wander::draw(graphics& g)
    {
    }
}
