#include "human_female.h"
#include "human_female_state.h"

namespace okunoshima
{
    void human_female::init()
    {
        m_movement_timer.set_callback([&]() {
            if (m_state) {
                m_state->update();
            }
        });
    }
    
    void human_female::check_state()
    {
        if (m_state) { m_state->check_state(); }
    }
    
    void human_female::update()
    {
        check_state();
        m_movement_timer.update();
    }
    
    void human_female::draw(graphics& g)
    {
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "entity_female.png");
        
        if (auto current_node = get_current_node()) {
            auto pos = current_node->get_position();
            auto size = vector2d{20, 20};
            
            g.draw_texture(*t, pos - size / 2);
        }
        
        if (m_state) { m_state->draw(g); }
    }
    
    void human_female::set_state(human_female_state_ptr state)
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

