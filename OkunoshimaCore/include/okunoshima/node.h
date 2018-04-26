#ifndef node_h
#define node_h

#include <vector>
#include "edge.h"
#include "vector2d.h"
#include "rect2d.h"

namespace okunoshima
{
    static const vector2d SIZE{20, 20};
    
    class graph_parser;
    class path_finding;
    class entity;
    
    using node_list = std::vector<node>;
    
    class node
    {
        friend class graph_parser;
        friend class path_finding;
        
        int m_id;
        vector2d m_position;
        rect2d m_bounds;
        std::vector<edge> m_edges;
        std::vector<entity*> m_entities;
        double m_g_cost = 0, m_h_cost = 0;
        node* m_parent = nullptr;
    protected:
        int f_cost() const { return m_g_cost + m_h_cost; }
        
    public:
        bool testme = false;
        
        node(int id, const vector2d& position) : m_id{id}, m_position{position}, m_bounds{position - SIZE / 2, position + SIZE / 2}, m_edges{}, m_entities{} {}
        
        void reset();
        void clear_agents();
        
        int get_id() const { return m_id; };
        vector2d get_position() const { return m_position; }
        rect2d get_bounds() const { return m_bounds; }
        decltype(auto) begin() { return m_edges.begin(); }
        decltype(auto) end() { return m_edges.end(); }
        std::vector<edge>& get_edges() { return m_edges; }
        
        bool add_entity(entity* ent);
        bool remove_entity(entity* ent);
        size_t number_of_entities() const { return m_entities.size(); }
        
        bool is_walkwable() const { return true; }
        
        friend std::ostream& operator<<(std::ostream& os, const node& n);
    };
    
    inline bool operator==(const node& lhs, const node& rhs)
    {
        return lhs.get_id() == rhs.get_id();
    }
    
    inline bool operator!=(const node& lhs, const node& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
