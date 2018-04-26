#include "node.h"
#include "edge.h"
#include "graph_parser.h"
#include "entity.h"
#include "rabbit.h"

namespace okunoshima
{
    void node::reset()
    {
        m_parent = nullptr;
        m_g_cost = 0;
        m_h_cost = 0;
    }
    
    void node::clear_agents()
    {
        std::vector<entity*> to_remove;
        
        for (auto e : m_entities) {
            auto r = dynamic_cast<rabbit*>(e);
            if (r) { to_remove.push_back(r); }
        }
        
        for (auto r : to_remove) {
            auto it = std::find(m_entities.begin(), m_entities.end(), r);
            if (it != m_entities.end()) {
                m_entities.erase(it);
            }
        }
        
        to_remove.clear();
    }
    
    bool node::add_entity(entity* ent)
    {
        auto it = std::find(m_entities.begin(), m_entities.end(), ent);
        if (it == m_entities.end()) {
            m_entities.push_back(ent);
            return true;
        }
        return false;
    }
    
    bool node::remove_entity(entity* ent)
    {
        auto it = std::find(m_entities.begin(), m_entities.end(), ent);
        if (it != m_entities.end()) {
            m_entities.erase(it);
            return true;
        }
        return false;
    }
    
    std::ostream& operator<<(std::ostream& os, const node& n)
    {
        os << "{id=" << n.m_id << ", position=" << n.m_position << '}';
        return os;
    }
}
