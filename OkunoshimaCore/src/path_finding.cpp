#include "path_finding.h"

namespace okunoshima
{
    bool path_finding::in_open(node* target)
    {
        auto it = std::find_if(m_open.begin(), m_open.end(), [&target](node* n) {
            return n->get_id() == target->get_id();
        });
        return it != m_open.end();
    }
    
    bool path_finding::in_closed(node* target)
    {
        auto it = std::find_if(m_closed.begin(), m_closed.end(), [&target](node* n) {
            return n->get_id() == target->get_id();
        });
        return it != m_closed.end();
    }
    
    bool path_finding::find(node* source, node* target)
    {
        source->reset();
        target->reset();
        
        for (auto& n : m_graph) {
            n.reset();
        }
        
        m_open.clear();
        m_closed.clear();
        
        // add source to open
        m_open.push_back(source);

        while (!m_open.empty()) {
            auto current_node = m_open.at(0);
            
            for (int i = 1; i < m_open.size(); ++i) {
                auto next_node = m_open.at(i);
                
                if (next_node->f_cost() <= current_node->f_cost()) {
                    if (next_node->m_h_cost < current_node->m_h_cost) {
                        current_node = next_node;
                    }
                }
            }
            
            m_open.erase(std::find(m_open.begin(), m_open.end(), current_node));
            m_closed.push_back(current_node);
            
            if (current_node->get_id() == target->get_id()) {
                trace(source, target);
                return true;
            }
            
            for (auto& current_edge : *current_node) {
                auto edge_node = &current_edge.get_to();
                
                if (in_closed(edge_node)) {
                    continue;
                }
                
                double new_cost = current_node->m_g_cost + manhattan_distance(current_node->get_position(), edge_node->get_position());
                
                if (new_cost < edge_node->m_g_cost || !in_open(edge_node)) {
                    edge_node->m_g_cost = new_cost;
                    edge_node->m_h_cost = manhattan_distance(edge_node->get_position(), target->get_position());
                    edge_node->m_parent = current_node;
                    
                    if (!in_open(edge_node)) {
                        m_open.push_back(edge_node);
                    }
                }
            }
        }
        return false;
    }
    
    void path_finding::trace(node* source, node* target)
    {
        m_path.clear();
        node* current_node = target;
        
        while (current_node->get_id() != source->get_id()) {
            m_path.push_back(current_node);
            current_node = current_node->m_parent;
        }
        
        std::reverse(m_path.begin(), m_path.end());
    }
}
