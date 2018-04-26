#include "genetic_strategy_random.h"

namespace okunoshima
{
    void genetic_strategy_random::setup(rabbit& agent)
    {
        auto& genes = agent.get_genes();
        genes["alignment"].randomize();
        genes["cohesion"].randomize();
        genes["separation"].randomize();
        genes["dog_attraction"].randomize();
        genes["water_attraction"].randomize();
        
        agent.print();
    }
}
