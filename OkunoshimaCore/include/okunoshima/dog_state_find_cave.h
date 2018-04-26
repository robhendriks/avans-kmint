#ifndef dog_state_find_cave_h
#define dog_state_find_cave_h

#include "dog_state.h"
#include "node.h"
#include "timer.h"
#include "progress_bar.h"

namespace okunoshima
{
    constexpr static const int MAX_SLEEP = 1000;
    
    class dog_state_find_cave : public dog_state
    {
        std::vector<node*> m_cave_path;
        timer m_sleep_timer;
        progress_bar m_sleep_progress_bar;
    public:
        dog_state_find_cave(dog& d) : dog_state{d, "find_cave"}, m_sleep_progress_bar{{1280, 10}, 0, MAX_SLEEP}
        {
            m_dog.set_drink_count(0);
            m_sleep_progress_bar.set_background({66, 165, 245});
            m_sleep_progress_bar.set_foreground({30, 136, 229});
        }
        
        void check_state() override;
        void leave() override;
        void update() override;
        void draw(graphics& g) override;
    };
}

#endif
