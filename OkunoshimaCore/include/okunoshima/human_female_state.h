#ifndef human_female_state_h
#define human_female_state_h

#include "human_female.h"
#include "graphics.h"

namespace okunoshima
{
    class human_female_state
    {
    protected:
        human_female& m_human;
    public:
        human_female_state(human_female& h) : m_human{h} {}

        virtual void enter() {}
        virtual void leave() {}
        virtual void check_state() = 0;
        virtual void update() = 0;
        virtual void draw(graphics& g) = 0;
    };
}

#endif
