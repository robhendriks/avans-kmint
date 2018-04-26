#ifndef align_h
#define align_h

#include "vector2d.h"
#include "rect2d.h"

namespace okunoshima
{
    // horiz.
    const unsigned char align_left = 1 << 0;
    const unsigned char align_center = 1 << 1;
    const unsigned char align_right = 1 << 2;
    
    // vert.
    const unsigned char align_top = 1 << 3;
    const unsigned char align_middle = 1 << 4;
    const unsigned char align_bottom = 1 << 5;
    
    const unsigned char align_default = align_left | align_top;
    
    inline void align(const rect2d& a, vector2d& b, const unsigned char options)
    {
        auto size = a.size();
        
        // horiz.
        if (options & align_left) {
            b.x = a.min.x;
        } else if (options & align_center) {
            b.x = a.min.x + size.x / 2;
        } else if (options & align_right) {
            b.x = a.max.x;
        }
        
        // vert.
        if (options & align_top) {
            b.y = a.min.y;
        } else if (options & align_middle) {
            b.y = a.min.y + size.y / 2;
        } else if (options & align_bottom) {
            b.y = a.max.y;
        }
    }
    
    inline void align(const vector2d& a, rect2d& b, const unsigned char options)
    {
        auto size = b.size();
        double x = a.x, y = a.y;
        
        // horiz.
        if (options & align_left) {
            x = a.x;
        } else if (options & align_center) {
            x = a.x - size.x / 2;
        } else if (options & align_right) {
            x = a.x - size.x;
        }
        
        // vert.
        if (options & align_top) {
            y = a.y;
        } else if (options & align_middle) {
            y = a.y - size.y / 2;
        } else if (options & align_bottom) {
            y = a.y - size.y;
        }
        
        b.move({x, y});
    }
    
    inline void align(const rect2d& a, rect2d& b, const unsigned char options)
    {
        auto size_a = a.size();
        auto size_b = b.size();
        
        double x = a.min.x, y = a.min.y;
        
        // horiz.
        if (options & align_left) {
            x = a.min.x;
        } else if (options & align_center) {
            x = a.min.x + size_a.x / 2 - size_b.x / 2;
        } else if (options & align_right) {
            x = a.max.x - size_b.x;
        }
        
        // vert.
        if (options & align_top) {
            y = a.min.y;
        } else if (options & align_middle) {
            y = a.min.y + size_a.y / 2 - size_b.y / 2;
        } else if (options & align_bottom) {
            y = a.max.y - size_b.y;
        }
        
        b.move({x, y});
    }
}

#endif
