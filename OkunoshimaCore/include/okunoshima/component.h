#ifndef component_h
#define component_h

#include <string>
#include "engine.h"

namespace okunoshima
{
    class component
    {
        std::string m_name;
        engine& m_engine;
    public:
        component(const std::string& name, engine& e) : m_name(name), m_engine{e}
        {
            e.m_components.emplace(name, this);
        }
        
        virtual void load() = 0;
        virtual void update() = 0;
        virtual void draw(graphics& g) = 0;
        
        const std::string& get_name() const { return m_name; }
        engine& get_engine() const { return m_engine; }
    };
}

#endif
