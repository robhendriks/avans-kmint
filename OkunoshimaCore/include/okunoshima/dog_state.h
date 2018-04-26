#ifndef dog_state_h
#define dog_state_h

#include <string>
#include "graphics.h"
#include "dog.h"

namespace okunoshima
{
    class dog_state
    {
    protected:
        dog& m_dog;
        std::string m_name;
    public:
        dog_state(dog& d, const std::string& name) : m_dog{d}, m_name{name} {}
        
        virtual void enter() {}
        virtual void leave() {}
        virtual void check_state() = 0;
        virtual void update() = 0;
        virtual void draw(graphics& g) = 0;
        
        virtual std::string get_name() const { return m_name; }
    };
}

#endif
