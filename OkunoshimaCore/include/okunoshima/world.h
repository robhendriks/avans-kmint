#ifndef world_h
#define world_h

#include "component.h"
#include "graph.h"
#include "graph_parser.h"
#include "entity_manager.h"
#include "path_finding.h"
#include "input.h"
#include "keyboard_listener.h"

namespace okunoshima
{
    class world : public component, public keyboard_listener
    {        
        graph m_graph;
        entity_manager m_entity_manager;
        bool m_debug_draw;
    public:
        world(engine& e) : component{"world", e}, m_entity_manager{*this}, m_debug_draw{false}
        {
            input::get_instance().get_keyboard().add_listener(*this);
        }
        
        ~world()
        {
            input::get_instance().get_keyboard().remove_listener(*this);
        }
        
        void load() override;
        void update() override;
        void draw(graphics& g) override;
        void draw_graph(graphics& g);
        void handle(const keyboard::event& e) override;
        
        dog* find_dog() const;
        human* find_human(human_type type) const;
        
        graph& get_graph() { return m_graph; }
        const graph& get_graph() const { return m_graph; }
        entity_manager& get_entity_manager() { return m_entity_manager; }
        const entity_manager& get_entity_manager() const { return m_entity_manager; }
    };
}

#endif
