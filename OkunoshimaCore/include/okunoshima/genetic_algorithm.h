#ifndef genetic_algorithm_h
#define genetic_algorithm_h

#include <vector>
#include "rabbit.h"

namespace okunoshima
{
    class genetic_strategy;
    class genetic_algorithm
    {
        int m_current_generation;
        std::vector<genetic_entity> m_parents;

        //        void crossover(); // merge the two best agents's properties
//        void mutation(); // loop agents: change 1 agents's properties randomly
        
        std::unique_ptr<genetic_strategy> get_strategy();
        
    public:
        genetic_algorithm() : m_current_generation{0}, m_parents{} {}
        
        void gather_parents(std::vector<rabbit*>& agents);
        void setup(std::vector<rabbit*>& agents);
        
        int get_current_generation() const { return m_current_generation; }
        
        std::vector<genetic_entity>& get_parents() { return m_parents; }
        const std::vector<genetic_entity>& get_parents() const { return m_parents; }
    };
}

#endif

