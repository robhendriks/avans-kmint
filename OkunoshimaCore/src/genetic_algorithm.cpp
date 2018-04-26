#include "genetic_algorithm.h"
#include "genetic_strategy.h"
#include "genetic_strategy_random.h"
#include "genetic_strategy_evolve.h"
#include "logger.h"

namespace okunoshima
{
    std::unique_ptr<genetic_strategy> genetic_algorithm::get_strategy()
    {
        if (m_current_generation > 0) {
            return std::make_unique<genetic_strategy_evolve>(*this);
        } else {
            return std::make_unique<genetic_strategy_random>(*this);
        }
    }
    
    void genetic_algorithm::gather_parents(std::vector<rabbit*>& agents)
    {
        if (m_current_generation == 0) { return; } // parent gathering not required the first time
        
        m_parents.clear();
        for (auto agent : agents) {
            agent->kill();
            m_parents.emplace_back(*agent);
        }
        
        logger::info("Gathered " + std::to_string(agents.size()) + " parent(s)...");
    }
    
    void genetic_algorithm::setup(std::vector<rabbit*>& agents)
    {
        auto strategy = get_strategy();
        
        logger::info("Generation " + std::to_string(m_current_generation + 1) + " (" + strategy->get_name() + ')');
        
        strategy->setup(agents);
        
        ++m_current_generation;
    }
}
