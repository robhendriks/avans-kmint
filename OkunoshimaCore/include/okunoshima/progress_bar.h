#ifndef progress_bar_h
#define progress_bar_h

#include "graphics.h"

namespace okunoshima
{    
    class progress_bar
    {
        vector2d m_size;
        rect2d m_outer_bounds;
        rect2d m_inner_bounds;
        double m_min;
        double m_max;
        double m_value;
        double m_percentage;
        color4f m_foreground{0, 255, 0};
        color4f m_background{255, 0, 0};
        
        void calculate_percentage();
        void calculate_bounds();
        
    public:
        progress_bar(const vector2d& size) : m_size{size}, m_min{0.0}, m_max{100.0}, m_value{50.0} { calculate_percentage(); }
        progress_bar(const vector2d& size, double value) : m_size{size}, m_min{0.0}, m_max{100.0}, m_value{value} { calculate_percentage(); }
        progress_bar(const vector2d& size, double min, double max, double value = 0.0) : m_size{size}, m_min{min}, m_max{max}, m_value{value} { calculate_percentage(); }
        
        void draw_at(const vector2d& vec, graphics& g);
        
        vector2d get_size() const {
            return m_size;
        }
        
        void set_size(const vector2d& size) {
            m_size = size;
            calculate_bounds();
        }
        
        double get_min() const {
            return m_min;
        }
        
        void set_min(double min) {
            m_min = min;
            set_value(m_value);
        }
        
        double get_max() const {
            return m_max;
        }
        
        void set_max(double max) {
            m_max = max;
            set_value(m_value);
        }
        
        double get_value() const {
            return m_value;
        }
        
        void set_value(double value) {
            m_value = std::clamp(value, m_min, m_max);
            calculate_percentage();
        }
        
        rect2d get_outer_bounds() const { return m_outer_bounds; }
        rect2d get_inner_bounds() const { return m_inner_bounds; }
        color4f get_foreground() const { return m_foreground; }
        void set_foreground(const color4f& foreground) { m_foreground = foreground; }
        color4f get_background() const { return m_background; }
        void set_background(const color4f& background) { m_background = background; }
    };
}

#endif /* progress_bar_h */
