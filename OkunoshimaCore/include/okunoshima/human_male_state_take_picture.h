#ifndef human_male_state_take_picture_h
#define human_male_state_take_picture_h

#include "human_male_state.h"
#include "random_utils.h"
#include "timer.h"

namespace okunoshima
{
    class human_male_state_take_picture : public human_male_state
    {
        timer m_timer;
    public:
        human_male_state_take_picture(human_male& h) : human_male_state{h} {}
        
        void enter() override;
        void check_state() override;
        void update() override;
        void draw(graphics& g) override;
    };
}

#endif
