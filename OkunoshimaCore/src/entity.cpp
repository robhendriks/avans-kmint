#include "entity.h"
#include "world.h"
#include "random_utils.h"

namespace okunoshima
{
    node* entity::wander_find_next_node(const std::vector<edge>& edges)
    {
        randomizer index{0, static_cast<int>(edges.size() - 1)};
        
        int i = 0;
        while (i < 10) {
            auto& edge = edges.at(index.random());
            if (edge.get_to().is_walkwable()) {
                return &edge.get_to();
            }
            ++i;
        }
        
        return nullptr;
    }
    
    node* entity::wander_next_node()
    {
        if (!m_current_node) { return nullptr; }
        
        auto& edges = m_current_node->get_edges();
        
        if (edges.size() > 1) {
            return wander_find_next_node(edges);
        } else if (edges.size() == 1) {
            auto& edge = edges.at(0);
            auto& target_node = edge.get_to();
            return target_node.is_walkwable() ? &target_node : nullptr;
        } else {
            return nullptr;
        }
    }
    
    void entity::wander()
    {
        auto next_node = wander_next_node();
        if (!next_node) {
            return;
        }
        
        set_current_node(next_node);
    }
}

