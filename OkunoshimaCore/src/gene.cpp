#include "gene.h"
#include "random_utils.h"

namespace okunoshima
{
    void gene::randomize()
    {
        randomizer r{static_cast<int>(m_lo_value * 100), static_cast<int>(m_hi_value * 100)};
        set_value(r.random() / 100.0);
    }
    
    void gene::print() const
    {
        std::cout << (*this) << std::endl;
    }
}
