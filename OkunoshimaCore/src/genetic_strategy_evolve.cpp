#include "genetic_strategy_evolve.h"
#include "logger.h"

namespace okunoshima
{
    const genetic_entity& genetic_strategy_evolve::get_fittest_parent() const
    {
        const auto& parents = get_context().get_parents();
        auto it = std::max_element(parents.begin(), parents.end(), [](const genetic_entity &a, const genetic_entity& b) {
            return a.get_alive_ticks() < b.get_alive_ticks();
        });
        return *it;
    }
    
    void genetic_strategy_evolve::calculate_fitness()
    {
        auto& parents = get_context().get_parents();
        
        double max_alive_ticks = get_fittest_parent().get_alive_ticks();
        for (auto& parent : parents) {
            parent.set_fitness((parent.get_alive_ticks() / max_alive_ticks) * 100);
        }
    }
    
    void genetic_strategy_evolve::populate_mating_pool()
    {
        m_mating_pool.clear();
        
        auto& parents = get_context().get_parents();
        
        for (auto& parent : parents) {
            int n = static_cast<int>(parent.get_fitness());
            for (int i = 0; i < n; ++i) {
                m_mating_pool.push_back(&parent);
            }
        }
        
        logger::info("Created mating pool of size " + std::to_string(m_mating_pool.size()));
    }
    
    void genetic_strategy_evolve::setup(std::vector<rabbit*>& agents)
    {
        calculate_fitness();
        populate_mating_pool();
        genetic_strategy::setup(agents);
        
        m_mating_pool.clear();
    }
    
    void genetic_strategy_evolve::setup(rabbit& agent)
    {
        randomizer r{0, static_cast<int>(m_mating_pool.size() - 1)};
        
        int a = r.random();
        int b = r.random();
        
        auto& parent_a = *m_mating_pool.at(a);
        auto& parent_b = *m_mating_pool.at(b);
        
//        parent_a.print();
//        parent_b.print();
        
        auto genes = parent_a.get_genes() + parent_b.get_genes();
        genes.mutate(1);
        agent.set_genes(genes);

        agent.print();
    }
}
