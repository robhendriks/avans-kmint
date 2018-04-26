#ifndef genetic_strategy_evolve_h
#define genetic_strategy_evolve_h

#include "genetic_strategy.h"
#include "random_utils.h"

namespace okunoshima
{
    class genetic_strategy_evolve : public genetic_strategy
    {
        std::vector<genetic_entity*> m_mating_pool;
        
        const genetic_entity& get_fittest_parent() const;
        void calculate_fitness();
        void populate_mating_pool();
    public:
        genetic_strategy_evolve(genetic_algorithm& context) : genetic_strategy{context, "evolve"} {}
        
        void setup(std::vector<rabbit*>& agents) override;
        void setup(rabbit& agent) override;
    };
}

#endif
