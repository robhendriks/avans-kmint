#ifndef human_female_h
#define human_female_h

#include "human.h"
#include "texture_manager.h"
#include "interval_timer.h"

namespace okunoshima
{
    class human_female_state;
    using human_female_state_ptr = std::shared_ptr<human_female_state>;
    
    class human_female : public human
    {
        human_female_state_ptr m_state;
        interval_timer m_movement_timer;
        
        void init();
    public:
        human_female(world* w) : human{"female", w, FEMALE}, m_movement_timer{300}
        {
            init();
        }
        
        void check_state();
        void update() override;
        void draw(graphics& g) override;
        
        human_female_state_ptr get_state() const { return m_state; }
        void set_state(human_female_state_ptr state);
    };
}

#endif

