#ifndef human_female_state_wait_h
#define human_female_state_wait_h

#include "human_female_state.h"

namespace okunoshima
{
    class human_female_state_wait : public human_female_state
    {
    public:
        human_female_state_wait(human_female& h) : human_female_state{h} {}

        void check_state() override;
        void update() override;
        void draw(graphics& g) override;
    };
}

#endif
