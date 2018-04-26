#include "dog.h"
#include "dog_state.h"
#include "dog_state_find_human.h"

namespace okunoshima
{
    void dog::init()
    {
        m_thirst_timer.set_callback([&]() {
            if (!m_sleeping) {
                this->set_thirst(m_thirst + 1);
            }
        });
        
        m_movement_timer.set_callback([&]() {
            if (m_state) {
                m_state->update();
            }
        });
    }
    
    void dog::check_state()
    {
        if (m_state) {
            m_state->check_state();
        }
    }
    
    void dog::update()
    {
        check_state();
        m_movement_timer.update();
        m_thirst_timer.update();
    }
    
    void dog::draw(graphics& g)
    {
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "entity_dog.png");
        
        if (auto current_node = get_current_node()) {
            auto pos = current_node->get_position();
            auto size = vector2d{20, 20};
            
            g.draw_texture(*t, pos - size / 2);
            
            m_thirst_progressbar.draw_at({pos.x, pos.y - 15}, g);
            
            if (m_debug_draw) {
                g.draw_string({pos.x, pos.y + 15}, m_state->get_name(), align_middle | align_center);
            }
        }
        
        if (m_state) {
            m_state->draw(g);
        }
    }
    
    void dog::handle(const keyboard::event& e)
    {
        if (e.type != keyboard::event::PRESSED) { return; }
        
        if (e.key_code == SDLK_d) {
            m_debug_draw = !m_debug_draw;
        }
        
        if (e.key_code == SDLK_t) {
            set_thirst(MAX_THIRST);
        }
    }
    
    void dog::set_state(dog_state_ptr state)
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

