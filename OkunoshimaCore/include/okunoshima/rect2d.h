#ifndef rect2d_h
#define rect2d_h

#include <SDL2/SDL.h>
#include "vector2d.h"

namespace okunoshima
{
    struct rect2d
    {
        vector2d min, max;
        
        rect2d() : min{}, max{}
        {
        }
        
        rect2d(const vector2d& min, const vector2d& max): min{min}, max{max}
        {
        }
        
        rect2d(double x1, double y1, double x2, double y2) : min{x1, y1}, max{x2, y2}
        {
        }
        
        rect2d(const rect2d& rect) : min{rect.min}, max{rect.max}
        {
        }
        
        bool intersects(const rect2d &r) const
        {
            return !((r.max.x < min.x || r.min.x > max.x) ||
                     (r.max.y < min.y || r.min.y > max.y));
        }
        
        rect2d& move(const vector2d& vec)
        {
            auto tmp_size = size();
            min = vec;
            max = min + tmp_size;
            return *this;
        }
        
        vector2d size() const
        {
            return max - min;
        }
        
        vector2d center() const
        {
            return (min + max) * 0.5f;
        }
        
        operator SDL_Rect() const
        {
            const vector2d vec = size();
            return {static_cast<int>(min.x),
                static_cast<int>(min.y),
                static_cast<int>(vec.x),
                static_cast<int>(vec.y)};
        }
    };
    
    inline void center(rect2d& a, const rect2d& b)
    {
        auto a_size = a.size();
        auto b_center = b.center();
        
        a.min = b_center - a_size / 2;
        a.max = a.min + a_size;
    }
    
    inline void center(rect2d& rect, const vector2d& vec)
    {
        auto size = rect.size();
        rect.min = vec - size / 2;
        rect.max = rect.min + size;
    }
}

#endif
