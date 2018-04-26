#include "human_male.h"
#include "human_male_state.h"

namespace okunoshima
{
    void human_male::init()
    {
        m_movement_timer.set_callback([&]() {
            if (m_state) {
                m_state->update();
            }
        });
    }
    
    void human_male::check_state()
    {
        if (m_state) { m_state->check_state(); }
    }
    
    void human_male::update()
    {
        check_state();
        m_movement_timer.update();
    }
    
    void human_male::draw(graphics& g)
    {
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "entity_male.png");
        
        if (auto current_node = get_current_node()) {
            auto pos = current_node->get_position();
            auto size = vector2d{20, 20};
            
            g.draw_texture(*t, pos - size / 2);
        }
        
        if (m_state) { m_state->draw(g); }
    }
    
    void human_male::set_state(human_male_state_ptr state)
    {
        if (m_state) {
            m_state->leave();
        }
        m_state = state;
        if (m_state) {
            m_state->enter();
        }
    }
}

