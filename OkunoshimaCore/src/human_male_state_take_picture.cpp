#include "human_male_state_take_picture.h"
#include "human_male_state_wander.h"
#include "texture_manager.h"

namespace okunoshima
{
    void human_male_state_take_picture::enter()
    {
        m_timer.start();
    }
    
    void human_male_state_take_picture::check_state()
    {
        if (m_timer.get_ticks() >= 10000) {
            m_timer.stop();
            m_human.set_state(std::make_shared<human_male_state_wander>(m_human));
        }
    }
    
    void human_male_state_take_picture::update()
    {
    }
    
    void human_male_state_take_picture::draw(graphics& g)
    {
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "camera.png");
        
        if (auto node = m_human.get_current_node()) {
            g.draw_texture(*t, node->get_position());
        }
    }
}
