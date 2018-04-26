#ifndef path_finding_h
#define path_finding_h

#include "graph.h"

namespace okunoshima
{
    class path_finding
    {
        std::vector<node*> m_open;
        std::vector<node*> m_closed;
        
        graph& m_graph;
        std::vector<node*> m_path;
        
        bool in_open(node* target);
        bool in_closed(node* target);
        
    public:
        path_finding(graph& g) : m_open{}, m_closed{}, m_graph{g} {}
        
        bool find(node* source, node* target);
        void trace(node* source, node* target);
        
        std::vector<node*> get_path() { return m_path; }
    };
}

#endif
