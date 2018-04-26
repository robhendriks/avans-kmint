#ifndef graph_h
#define graph_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "node.h"
#include "color4f.h"
#include <tuple>

namespace okunoshima
{
    class graph_parser;
    class graph
    {
        friend class graph_parser;
        
        std::vector<node> m_nodes;
        std::map<std::string, std::tuple<color4f, node*>> m_spawn_nodes;
    public:
        decltype(auto) begin() { return m_nodes.begin(); }
        decltype(auto) begin() const { return m_nodes.begin(); }
        decltype(auto) end() { return m_nodes.end(); }
        decltype(auto) end() const { return m_nodes.end(); }
        decltype(auto) size() const { return m_nodes.size(); }
        
        std::vector<node>& get_nodes() { return m_nodes; }
        
        std::map<std::string, std::tuple<color4f, node*>>& get_spawn_nodes() { return m_spawn_nodes; }
        const std::map<std::string, std::tuple<color4f, node*>>& get_spawn_nodes() const { return m_spawn_nodes; }
    };
}

#endif
