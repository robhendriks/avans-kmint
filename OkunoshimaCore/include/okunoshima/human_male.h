#ifndef human_male_h
#define human_male_h

#include "human.h"
#include "texture_manager.h"
#include "interval_timer.h"

namespace okunoshima
{
    class human_male_state;
    using human_male_state_ptr = std::shared_ptr<human_male_state>;
    
    class human_male : public human
    {
        human_male_state_ptr m_state;
        interval_timer m_movement_timer;
        
        void init();
    public:
        human_male(world* w) : human{"male", w, MALE}, m_movement_timer{300}
        {
            init();
        }
        
        void check_state();
        void update() override;
        void draw(graphics& g) override;
        
        human_male_state_ptr get_state() const { return m_state; }
        void set_state(human_male_state_ptr state);
    };
}

#endif

