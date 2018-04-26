#ifndef vector2d_h
#define vector2d_h

#include <iostream>
#include <cmath>

namespace okunoshima
{
    struct vector2d
    {
        double x, y;
        
        vector2d(): x{0}, y{0}
        {
        }
        
        vector2d(double x, double y) : x{x}, y{y}
        {
        }
        
        vector2d(const vector2d& vec) : x{vec.x}, y{vec.y}
        {
        }
        
        //
        // Instance methods
        //
        
        double length() const
        {
            return std::sqrt(x * x + y * y);
        }
        
        double length2() const
        {
            return x * x + y * y;
        }
        
        double manhattan_length() const
        {
            return std::abs(x) + std::abs(y);
        }
        
        vector2d& normalize()
        {
            double l = length();
            if (l != 0) {
                x /= l;
                y /= l;
            }
            return *this;
        }
        
        vector2d& limit(float max)
        {
            if (length2() > max * max) {
                normalize();
                operator*=(max);
            }
            return *this;
        }
        
        vector2d& set_magnitude(float max)
        {
            normalize();
            operator*=(max);
            return *this;
        }
        
        void print() const
        {
            std::cout << (*this) << std::endl;
        }
        
        //
        // Assignment
        //
        
        vector2d& operator=(const vector2d& vec)
        {
            if (this != &vec) {
                x = vec.x;
                y = vec.y;
            }
            return *this;
        }
        
        //
        // Increment and decrement
        //
        
        vector2d& operator++()
        {
            ++x;
            ++y;
            return *this;
        }
        
        vector2d operator++(int)
        {
            vector2d tmp{*this};
            operator++();
            return tmp;
        }
        
        vector2d& operator--()
        {
            --x;
            --y;
            return *this;
        }
        
        vector2d operator--(int)
        {
            vector2d tmp{*this};
            operator--();
            return tmp;
        }
        
        //
        // Arithmetic
        //
        
        vector2d& operator+=(float rhs)
        {
            x += rhs;
            y += rhs;
            return *this;
        }
        
        vector2d& operator+=(const vector2d& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        
        vector2d& operator-=(float rhs)
        {
            x -= rhs;
            y -= rhs;
            return *this;
        }
        
        vector2d& operator-=(const vector2d& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        
        vector2d& operator*=(float rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }
        
        vector2d& operator*=(const vector2d& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }
        
        vector2d& operator/=(float rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }
        
        vector2d& operator/=(const vector2d& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }
        
        //
        // Stream extraction and insertion
        //
      
        friend std::istream& operator>>(std::istream& is, vector2d& vec);
        friend std::ostream& operator<<(std::ostream& os, const vector2d& vec);
    };
    
    //
    // Static methods
    //
    
    inline double distance(const vector2d& a, const vector2d& b)
    {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    inline double manhattan_distance(const vector2d& a, const vector2d& b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
    
    inline void min(const vector2d& a, const vector2d& b, vector2d& c)
    {
        c.x = std::min(a.x, b.x);
        c.y = std::min(a.y, b.y);
    }
    
    inline vector2d min(const vector2d& a, const vector2d& b)
    {
        vector2d tmp;
        min(a, b, tmp);
        return tmp;
    }
    
    inline void max(const vector2d& a, const vector2d& b, vector2d& c)
    {
        c.x = std::max(a.x, b.x);
        c.y = std::max(a.y, b.y);
    }
    
    inline vector2d max(const vector2d& a, const vector2d& b)
    {
        vector2d tmp;
        max(a, b, tmp);
        return tmp;
    }
    
    //
    // Arithmetic
    //
    
    inline vector2d operator+(vector2d lhs, float rhs)
    {
        lhs += rhs;
        return lhs;
    }
    
    inline vector2d operator+(vector2d lhs, const vector2d& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    
    inline vector2d operator-(vector2d lhs, float rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    
    inline vector2d operator-(vector2d lhs, const vector2d& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    
    inline vector2d operator*(vector2d lhs, float rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    
    inline vector2d operator*(vector2d lhs, const vector2d& rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    
    inline vector2d operator/(vector2d lhs, float rhs)
    {
        lhs /= rhs;
        return lhs;
    }
    
    inline vector2d operator/(vector2d lhs, const vector2d& rhs)
    {
        lhs /= rhs;
        return lhs;
    }
    
    //
    // Relational
    //
    
    inline bool operator<(const vector2d& lhs, const vector2d& rhs)
    {
        return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
    }
    
    inline bool operator>(const vector2d& lhs, const vector2d& rhs)
    {
        return rhs < lhs;
    }
    
    inline bool operator<=(const vector2d& lhs, const vector2d& rhs)
    {
        return !(lhs > rhs);
    }
    
    inline bool operator>=(const vector2d& lhs, const vector2d& rhs)
    {
        return !(lhs < rhs);
    }
    
    inline bool operator==(const vector2d& lhs, const vector2d& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    
    inline bool operator!=(const vector2d& lhs, const vector2d& rhs)
    {
        return !(lhs == rhs);
    }
    
    //
    // Stream extraction and insertion
    //
    
    inline std::ostream& operator<<(std::ostream& os, const vector2d& vec)
    {
        os << "vector2d(x=" << vec.x << ", y=" << vec.y << ')';
        return os;
    }
    
    inline std::istream& operator>>(std::istream& is, vector2d& vec)
    {
        double x, y;
        if (is >> x && is >> y) {
            vec.x = x;
            vec.y = y;
        }
        return is;
    }
}

#endif
