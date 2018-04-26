#include "rabbit.h"
#include "world.h"

namespace okunoshima
{
    void rabbit::update()
    {        
        if (!is_alive()) { return; }
        
        auto& g = get_world().get_graph();
        auto& em = get_world().get_entity_manager();
        
        if (auto dog = em.find_dog()) {
            auto dog_node = dog->get_current_node();
            auto rabbit_node = get_current_node();
            
            if (dog_node && rabbit_node) {
                if (distance(dog_node->get_position(), rabbit_node->get_position()) <= 15) {
                    kill();
                    return;
                }
            }
        }
        
        for (auto& n : g) {
            auto dist = distance(n.get_position(), m_position);
            
//            if (dist <= 28.2842712475) {
            if (dist <= 14.1421356237) {
//            if (n.get_bounds().intersects(get_bounds())) {
                n.add_entity(this);
                add_node(&n);
            } else {
                n.remove_entity(this);
                remove_node(&n);
            }
        }
        
        force_driven_entity::update();
    }
    
    void rabbit::draw(graphics& g)
    {
        force_driven_entity::draw(g);
        
        auto tm = texture_manager::get_instance();
        auto t = tm->load(g, "entity_rabbit.png");
    
        g.draw_texture(*t, m_position - t->get_size() / 2);
    }
    
    node* rabbit::get_current_node()
    {
        return !m_current_nodes.empty() ? m_current_nodes.front() : nullptr;
    }
}

