#include "genetic_strategy.h"

namespace okunoshima
{
    void genetic_strategy::setup(std::vector<rabbit*> &agents)
    {
        for (auto agent : agents) {
            if (agent != nullptr) {
                setup(*agent);
//                agent->get_genes().print();
            }
        }
    }
}
