#ifndef dog_h
#define dog_h

#include <memory>
#include "animal.h"
#include "texture_manager.h"
#include "interval_timer.h"
#include "progress_bar.h"
#include "input.h"
#include "keyboard_listener.h"
#include "align.h"
#include "colors.h"

namespace okunoshima
{
    constexpr static const int MIN_THIRST = 0;
    constexpr static const int MAX_THIRST = 100;
    constexpr static const int ATTACK_RADIUS = 50;

    class dog_state;
    using dog_state_ptr = std::shared_ptr<dog_state>;

    class dog : public animal, public keyboard_listener
    {
        interval_timer m_thirst_timer;
        interval_timer m_movement_timer;
        dog_state_ptr m_state;
        int m_thirst;
        int m_drink_count;
        int m_drink_change;
        int m_last_drink_amount;
        bool m_sleeping;
        progress_bar m_thirst_progressbar;
        bool m_debug_draw;

        void init();
        void check_state();

    public:
        dog(world* w) : animal{"dog", w}, m_state{nullptr}, m_thirst{0}, m_drink_count{0}, m_sleeping{false}, m_thirst_progressbar{{30, 3}, 75}, m_thirst_timer{1000},  m_movement_timer{150}, m_debug_draw{false}
        {
            m_thirst_progressbar.set_foreground(lighten(colors::blue, 10));
            m_thirst_progressbar.set_background(darken(colors::blue, 10));
            m_thirst_progressbar.set_value(m_thirst);
            m_drink_change = 50;
            m_last_drink_amount = 0;

            input::get_instance().get_keyboard().add_listener(*this);

            init();
        }

        ~dog()
        {
            input::get_instance().get_keyboard().remove_listener(*this);
        }

        dog_state_ptr get_state() const { return m_state; }
        void set_state(dog_state_ptr state);

        void update() override;
        void draw(graphics& g) override;
        void handle(const keyboard::event& e) override;

        int get_thirst() const { return m_thirst; }

        void set_thirst(int thirst)
        {
            m_thirst = std::clamp(thirst, MIN_THIRST, MAX_THIRST);
            m_thirst_progressbar.set_value(m_thirst);
        }

        int get_drink_count() const { return m_drink_count; }
        void set_drink_count(int drink_count) { m_drink_count = drink_count; }
        bool is_sleeping() const { return m_sleeping; }
        void set_sleeping(bool sleeping) { m_sleeping = sleeping; }

        int get_drink_change() const { return m_drink_change; }
        void set_drink_change(int drink_change) { m_drink_change = drink_change; }

        int get_last_drink_amount() const { return m_last_drink_amount; }
        void set_last_drink_amount(int last_drink_amount) { m_last_drink_amount = last_drink_amount; }
    };
}

#endif
