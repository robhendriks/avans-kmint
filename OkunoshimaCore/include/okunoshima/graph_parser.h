#ifndef graph_parser_h
#define graph_parser_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "graph.h"
#include "color4f.h"

namespace okunoshima
{
    class graph_parser
    {
        std::string m_file_name;
        int m_line_number;
        int m_empty_count;
        
        enum PARSE_MODE
        {
            NODE,
            EDGE,
            SPAWN
        } m_mode;
        
    public:
        graph_parser(const std::string& file_name) : m_file_name{file_name}, m_line_number{-1}, m_empty_count{-1}, m_mode{NODE} {}
        void parse(graph& g);
        void parse_node(graph& g, std::istringstream& ss);
        void parse_edge(graph& g, std::istringstream& ss);
        void parse_spawn(graph& g, std::istringstream& ss);
    };
}

#endif
