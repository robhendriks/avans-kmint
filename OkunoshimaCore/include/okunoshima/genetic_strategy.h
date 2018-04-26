#ifndef genetic_strategy_h
#define genetic_strategy_h

#include <string>
#include "genetic_algorithm.h"
#include "rabbit.h"

namespace okunoshima
{
    class genetic_strategy
    {
        genetic_algorithm& m_context;
        const std::string m_name;
    protected:
        genetic_algorithm& get_context() { return m_context; }
        const genetic_algorithm& get_context() const { return m_context; }
        
    public:
        genetic_strategy(genetic_algorithm& context, const std::string& name) : m_context{context}, m_name{name} {}
        
        virtual void setup(std::vector<rabbit*>& agents);
        
        virtual void setup(rabbit& agent) = 0;
        
        std::string get_name() const { return m_name; }
    };
}

#endif
