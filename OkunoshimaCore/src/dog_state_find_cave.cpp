#include "dog_state_find_cave.h"
#include "world.h"
#include "path_finding.h"
#include "dog_state_wander.h"
#include "logger.h"
#include "colors.h"

namespace okunoshima
{
    void dog_state_find_cave::check_state()
    {
        if (m_sleep_timer.get_ticks() >= MAX_SLEEP) {
            m_dog.set_state(std::make_shared<dog_state_wander>(m_dog));
        }
    }
    
    void dog_state_find_cave::leave()
    {
        m_dog.set_sleeping(false);
        m_dog.get_world().get_entity_manager().reset();
    }
    
    void dog_state_find_cave::update()
    {
        auto& w = m_dog.get_world();
        auto cave_node = std::get<1>(w.get_graph().get_spawn_nodes()["dog"]);
        
        if (m_dog.get_current_node() == cave_node) {
            if (!m_dog.is_sleeping()) {
                m_sleep_timer.start();
                m_dog.set_sleeping(true);
            } else {
                m_sleep_progress_bar.set_value(m_sleep_timer.get_ticks());
            }
        } else if (m_cave_path.empty()) {
            if (auto dog_node = m_dog.get_current_node()) {
                path_finding pf{w.get_graph()};
                if (pf.find(dog_node, cave_node)) {
                    m_cave_path = pf.get_path();
                    logger::info("Dog found path to cave");
                } else {
                    m_cave_path.clear();
                    logger::warn("Dog could not determine path to cave");
                }
            }
        } else {
            m_dog.set_current_node(m_cave_path.front());
            m_cave_path.erase(m_cave_path.begin());
        }
    }
    
    void dog_state_find_cave::draw(graphics& g)
    {
        if (!m_cave_path.empty()) {
            g.draw_path(colors::deep_purple, m_cave_path);
        }
        
        if (m_dog.is_sleeping()) {
            m_sleep_progress_bar.draw_at({640, 5}, g);
            g.draw_string(m_sleep_progress_bar.get_outer_bounds(), "Generating new population...", align_center | align_middle);
        }
    }
}
