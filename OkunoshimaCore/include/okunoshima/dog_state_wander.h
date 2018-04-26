#ifndef dog_state_wander_h
#define dog_state_wander_h

#include "dog_state.h"
#include "random_utils.h"

namespace okunoshima
{
    class dog_state_wander : public dog_state
    {
    public:
        dog_state_wander(dog& d) : dog_state{d, "wander"} {}
        
        void check_state() override;
        void update() override;
        void draw(graphics& g) override;
    };
}

#endif
