#ifndef dog_state_attack_h
#define dog_state_attack_h

#include "dog_state.h"
#include "node.h"

namespace okunoshima
{
    class rabbit;
    class dog_state_attack : public dog_state
    {
        std::vector<node*> m_path;
        rabbit* m_target;
    public:
        dog_state_attack(dog& d, rabbit* target) : dog_state{d, "attack"}, m_target{target} {}
        
        void check_state() override;
        void update() override;
        void draw(graphics& g) override;
    };
}

#endif
