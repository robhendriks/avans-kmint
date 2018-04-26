#include "dog_state_attack.h"
#include "dog_state_find_human.h"
#include "dog_state_wander.h"
#include "world.h"
#include "rabbit.h"
#include "logger.h"
#include "path_finding.h"
#include "colors.h"

namespace okunoshima
{
    void dog_state_attack::check_state()
    {
        if (m_dog.get_thirst() >= MAX_THIRST) {
            m_dog.set_state(std::make_shared<dog_state_find_human>(m_dog));
        }
        
        auto& em = m_dog.get_world().get_entity_manager();
        if (!em.agents_in_radius(m_dog, ATTACK_RADIUS)) {
            m_dog.set_state(std::make_shared<dog_state_wander>(m_dog));
        }
    }
    
    void dog_state_attack::update()
    {
        auto& w = m_dog.get_world();
        
        if (m_target && !m_target->is_alive()) {
            m_dog.set_state(std::make_shared<dog_state_wander>(m_dog));
        } else if (m_target) {
            if (m_path.empty()) {
                auto dog_node = m_dog.get_current_node();
                auto target_node = m_target->get_current_node();
                
                if (dog_node && target_node) {
                    path_finding pf{w.get_graph()};
                    if (pf.find(dog_node, m_target->get_current_node())) {
                        m_path = pf.get_path();
                        logger::info("Dog found path to rabbit");
                    } else {
                        m_path.clear();
                        logger::warn("Dog could not determine path to rabbit");
                    }
                }
            } else {
                m_dog.set_current_node(m_path.front());
                m_path.erase(m_path.begin());
            }
        }
    }
    
    void dog_state_attack::draw(graphics& g)
    {
        if (!m_path.empty()) {
            g.draw_path(colors::red, m_path);
        }
        
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "entity_dog_angry.png");
        
        if (auto current_node = m_dog.get_current_node()) {
            auto pos = current_node->get_position();
            auto size = vector2d{20, 20};
            
            g.draw_texture(*t, pos - size / 2);
        }
    }
}
