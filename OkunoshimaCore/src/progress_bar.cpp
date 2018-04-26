#include "progress_bar.h"

namespace okunoshima
{
    void progress_bar::calculate_percentage()
    {
        m_percentage = (m_value - m_min) / (m_max - m_min) * 100;
        calculate_bounds();
    }
    
    void progress_bar::calculate_bounds()
    {
        m_outer_bounds.min = {0, 0};
        m_outer_bounds.max = m_size;
    }
    
    void progress_bar::draw_at(const vector2d& vec, graphics& g)
    {
        center(m_outer_bounds, vec);
        
        m_inner_bounds.min = m_outer_bounds.min;
        m_inner_bounds.max = m_inner_bounds.min + vector2d{m_size.x / 100 * m_percentage, m_size.y};
        
        g.fill_rect(m_background, m_outer_bounds);
        g.fill_rect(m_foreground, m_inner_bounds);
    }
}
