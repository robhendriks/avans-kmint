#ifndef dog_state_find_human_h
#define dog_state_find_human_h

#include "dog_state.h"
#include "human.h"

namespace okunoshima
{
    class dog_state_find_human : public dog_state
    {
        human* m_target;
        vector2d m_target_position;
        std::vector<node*> m_target_path;
        
        void update_target_position(node* target);
        
    public:
        dog_state_find_human(dog& d) : dog_state{d, "find_human"}, m_target{nullptr} {}
        
        void check_state() override;
        void update() override;
        void draw(graphics& g) override;
        
        std::string get_name() const override;
    };
}

#endif
