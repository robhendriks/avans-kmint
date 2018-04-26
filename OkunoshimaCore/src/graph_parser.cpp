#include "graph_parser.h"

namespace okunoshima
{
    void graph_parser::parse(graph &g)
    {
        std::ifstream is{m_file_name};
        
        m_line_number = 1;
        m_empty_count = 0;
        m_mode = NODE;
        
        for (std::string line; std::getline(is, line);) {
            if (line == "") {
                ++m_empty_count;
                m_mode = m_empty_count > 1 ? SPAWN : EDGE;
                ++m_line_number;
                continue;
            }
            
            std::istringstream ss{line};
            switch (m_mode) {
                case NODE:
                    parse_node(g, ss); break;
                case EDGE:
                    parse_edge(g, ss); break;
                case SPAWN:
                    parse_spawn(g, ss);
            }
            
            ++m_line_number;
        }
    }
    
    void graph_parser::parse_node(graph& g, std::istringstream& ss)
    {
        vector2d vec;
        if (ss >> vec) {
            g.m_nodes.emplace_back(g.size(), vec);
        } else {
            throw std::runtime_error{"error reading node at line " + std::to_string(m_line_number)};
        }
    }
    
    void graph_parser::parse_edge(graph& g, std::istringstream& ss)
    {
        int from_id, to_id;
        float weight;
        if (ss >> from_id && ss >> to_id && ss >> weight) {
            auto& from = g.m_nodes.at(from_id);
            auto& to = g.m_nodes.at(to_id);
            from.m_edges.emplace_back(from, to, weight);
        } else {
            throw std::runtime_error{"error reading edge at line " + std::to_string(m_line_number)};
        }
    }
    
    void graph_parser::parse_spawn(graph& g, std::istringstream& ss)
    {
        std::string name;
        int id;
        color4f color;
        if (ss >> name && ss >> id && ss >> color) {
            auto node = &g.m_nodes.at(id);
            g.m_spawn_nodes.emplace(name, std::make_tuple(color, node));
        } else {
            throw std::runtime_error{"error reading spawn at line " + std::to_string(m_line_number)};
        }
    }
}
