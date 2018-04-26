#ifndef entity_h
#define entity_h

#include <vector>
#include "graphics.h"
#include "node.h"

namespace okunoshima
{
    class world;
    class entity
    {
        const std::string m_name;
        world* m_world;
        node* m_current_node;
        
    protected:
        node* wander_find_next_node(const std::vector<edge>& edges);
        node* wander_next_node();
        
    public:
        entity(const std::string& name, world* w) : m_name{name}, m_world{w}, m_current_node{nullptr} {}
        
        void wander();
        virtual void update() = 0;
        virtual void draw(graphics& g) = 0;
        
        const std::string& get_name() const { return m_name; }
        
        world& get_world() { return *m_world; }
        const world& get_world() const { return *m_world; }
        
        virtual node* get_current_node() { return m_current_node; }
        
        virtual void set_current_node(node* current_node) {
            if (m_current_node) {
                m_current_node->remove_entity(this);
            }
            m_current_node = current_node;
            if (m_current_node) {
                m_current_node->add_entity(this);
            }
        }
    };
}

#endif

