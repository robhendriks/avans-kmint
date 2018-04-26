#ifndef edge_h
#define edge_h

#include <ostream>

namespace okunoshima
{
    class node;
    class edge
    {
        node* m_from;
        node* m_to;
        float m_weight;
    public:
        edge(node& from, node& to, float weight) : m_from{&from}, m_to{&to}, m_weight{weight} {}
        node& get_from() const { return *m_from; }
        node& get_to() const { return *m_to; }
        float get_weight() const { return m_weight; }
        
        friend std::ostream& operator<<(std::ostream& os, const edge& e);
    };
}

#endif
