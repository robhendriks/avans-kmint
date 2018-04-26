#ifndef genetic_strategy_random_h
#define genetic_strategy_random_h

#include "genetic_strategy.h"
#include "random_utils.h"

namespace okunoshima
{
    class genetic_strategy_random : public genetic_strategy
    {
    public:
        genetic_strategy_random(genetic_algorithm& context) : genetic_strategy{context, "random"} {}
        
        void setup(rabbit& agent) override;
    };
}

#endif
