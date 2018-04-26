#include "edge.h"
#include "node.h"

namespace okunoshima
{
    std::ostream& operator<<(std::ostream& os, const edge& e)
    {
        os << "{from=" << e.get_from().get_id() << ", to=" << e.get_to().get_id() << ", weight=" << e.m_weight << '}';
        return os;
    }
}
