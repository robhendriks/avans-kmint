#include "world.h"
#include "colors.h"

namespace okunoshima
{
    void world::load()
    {
        graph_parser parser{"graph.txt"};
        parser.parse(m_graph);
        
        m_entity_manager.load();
    }
    
    dog* world::find_dog() const
    {
        return m_entity_manager.find_dog();
    }
    
    human* world::find_human(human_type type) const
    {
        return m_entity_manager.find_human(type);
    }
    
    void world::update()
    {
        m_entity_manager.update();
    }
    
    void world::draw(graphics& g)
    {
        draw_graph(g);
        m_entity_manager.draw(g);
        
#ifdef DEBUG_DRAW
        for (auto& n : m_graph) {
            g.draw_string(n.get_position(), std::to_string(n.number_of_entities()));
        }
#endif
    }
    
    void world::draw_graph(graphics& g)
    {
        rect2d small{0, 0, 4, 4};
        
        for (auto& n : m_graph) {
            g.set_color(colors::green);
            g.fill_rect(n.get_bounds());
            
            if (!m_debug_draw) { continue; }
            
            g.set_color(lighten(colors::green, 10));
            
            for (auto& e : n) {
                center(small, e.get_from().get_bounds());
                g.fill_rect(small);
                g.draw_line(e.get_from().get_position(), e.get_to().get_position());
            }
        }
        
        for (auto& pair : m_graph.get_spawn_nodes()) {
            auto& color = std::get<0>(pair.second);
            auto n = std::get<1>(pair.second);
            
            g.set_color(color);
            g.fill_rect(n->get_bounds());
        }
    }
    
    void world::handle(const keyboard::event& e)
    {
        if (e.type != keyboard::event::PRESSED) { return; }
        
        if (e.key_code == SDLK_w) {
            m_debug_draw = !m_debug_draw;
        }
    }
}
