#ifndef human_male_state_h
#define human_male_state_h

#include "human_male.h"
#include "graphics.h"

namespace okunoshima
{
    class human_male_state
    {
    protected:
        human_male& m_human;
    public:
        human_male_state(human_male& h) : m_human{h} {}
        
        virtual void enter() {}
        virtual void leave() {}
        virtual void check_state() = 0;
        virtual void update() = 0;
        virtual void draw(graphics& g) = 0;
    };
}

#endif
