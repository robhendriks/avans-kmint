#ifndef color4f_h
#define color4f_h

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include "string_utils.h"

namespace okunoshima
{
    static const std::regex hex_regex("^#?([a-fA-F0-9]{6})$");
    
    struct color4f
    {
        double r, g, b, a;
        
        color4f() : r{0.0}, g{0.0}, b{0.0}, a{255.0} {}
        color4f(double r, double g, double b) : r{r}, g{g}, b{b}, a{255.0} {}
        color4f(double r, double g, double b, double a) : r{r}, g{g}, b{b}, a{a} {}
        color4f(const color4f& col) : r{col.r}, g{col.g}, b{col.b}, a{col.a} {}
        
        color4f(uint32_t hex)
        {
            set_hex(hex);
        }
        
        color4f(const std::string& hex)
        {
            if (!std::regex_match(hex, hex_regex)) {
                throw std::invalid_argument(std::string("Error: invalid HEX; ") + hex);
            }
            set_hex(std::stoi(ltrimmed(hex, '#'), nullptr, 16));
        }
        
        void set_hex(uint32_t hex)
        {
            r = (hex >> 16) & 0xFF;
            g = (hex >> 8) & 0xFF;
            b = hex & 0xFF;
            a = 255.0;
        }
        
        void print() const
        {
            std::cout << (*this) << std::endl;
        }
        
        color4f &operator+=(const color4f &col) {
            r += col.r;
            g += col.g;
            b += col.b;
            return *this;
        }
        
        color4f &operator-=(const color4f &col) {
            r -= col.r;
            g -= col.g;
            b -= col.b;
            return *this;
        }
        
        friend std::istream& operator>>(std::istream& is, color4f& col);
        friend std::ostream& operator<<(std::ostream& os, const color4f& col);
    };
    
    inline color4f operator+(color4f lhs, const color4f &rhs) {
        lhs += rhs;
        return lhs;
    }
    
    inline color4f operator-(color4f lhs, const color4f &rhs) {
        lhs -= rhs;
        return lhs;
    }
    
    struct color_hsl {
        double h;
        double s;
        double l;
    };
    
    static inline double h_to_rgb(double m1, double m2, double h) {
        while (h < 0) h += 1;
        while (h > 1) h -= 1;
        if (h * 6.0 < 1) return m1 + (m2 - m1) * h * 6;
        if (h * 2.0 < 1) return m2;
        if (h * 3.0 < 2) return m1 + (m2 - m1) * (2.0 / 3.0 - h) * 6;
        return m1;
    }
    
    static inline color_hsl rgb_to_hsl(const color4f &rgb) {
        double r = rgb.r / 255.0;
        double g = rgb.g / 255.0;
        double b = rgb.b / 255.0;
        
        double max = std::max(r, std::max(g, b));
        double min = std::min(r, std::min(g, b));
        double delta = max - min;
        
        double h = 0, s = 0, l = (max + min) / 2.0;
        
        if (max == min) {
            h = s = 0; // achromatic
        } else {
            if (l < 0.5) s = delta / (max + min);
            else s = delta / (2.0 - max - min);
            
            if (r == max) h = (g - b) / delta + (g < b ? 6 : 0);
            else if (g == max) h = (b - r) / delta + 2;
            else if (b == max) h = (r - g) / delta + 4;
        }
        
        return {h / 6 * 360, s * 100, l * 100};
    }
    
    static inline color4f hsl_to_rgb(const color_hsl &hsl, double a) {
        color4f result;
        
        double h, s, l;
        h = hsl.h / 360.0;
        s = hsl.s / 100.0;
        l = hsl.l / 100.0;
        
        if (l < 0) l = 0;
        if (s < 0) s = 0;
        if (l > 1) l = 1;
        if (s > 1) s = 1;
        while (h < 0) h += 1;
        while (h > 1) h -= 1;
        
        if (s == 0) s = 1e-10;
        
        double m2;
        if (l <= 0.5) m2 = l * (s + 1.0);
        else m2 = (l + s) - (l * s);
        double m1 = (l * 2.0) - m2;
        
        double r = (h_to_rgb(m1, m2, h + 1.0 / 3.0) * 255.0);
        double g = (h_to_rgb(m1, m2, h) * 255.0);
        double b = (h_to_rgb(m1, m2, h - 1.0 / 3.0) * 255.0);
        
        return {r, g, b, a};
    }
    
    static inline color4f darken(const color4f &col, double amount) {
        amount = std::clamp(amount, 0.0, 100.0);
        
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.l = std::clamp(hsl.l - amount, 0.0, 100.0); // Ramp and decrease lightness
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f lighten(const color4f &col, double amount) {
        amount = std::clamp(amount, 0.0, 100.0);
        
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.l = std::clamp(hsl.l + amount, 0.0, 100.0); // Ramp and increase lightness
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f hue(const color4f &col, double degrees) {
        color_hsl hsl = rgb_to_hsl(col);
        hsl.h += degrees;
        return hsl_to_rgb(hsl, col.a);
    }
    
    static inline color4f saturate(const color4f &col, double amount) {
        amount = std::clamp(amount, 0.0, 100.0);
        
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.s = std::clamp(hsl.s + amount, 0.0, 100.0); // Ramp and increase saturation
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f desaturate(const color4f &col, double amount) {
        amount = std::clamp(amount, 0.0, 100.0);
        
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.s = std::clamp(hsl.s - amount, 0.0, 100.0); // Ramp and decrease saturation
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f greyscale(const color4f &col) {
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.s = 0.0; // Decrease saturation
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f complement(const color4f &col) {
        color_hsl hsl = rgb_to_hsl(col); // Convert to HSL
        hsl.h -= 180.0; // Modify hue
        
        return hsl_to_rgb(hsl, col.a); // Convert to RGB
    }
    
    static inline color4f invert(const color4f &col) {
        return {255.0 - col.r, 255.0 - col.g, 255.0 - col.b};
    }
    
    static inline color4f mix(const color4f &col1, const color4f &col2, double weight) {
        weight = std::clamp(weight, 0.0, 100.0);
        
        double p = weight / 100;
        double w = 2 * p - 1;
        double a = col1.a - col2.a;
        
        double w1 = (((w * a == -1) ? w : (w + a) / (1 + w * a)) + 1) / 2.0;
        double w2 = 1 - w1;
        
        return color4f{w1 * col1.r + w2 * col2.r,
            w1 * col1.g + w2 * col2.g,
            w1 * col1.b + w2 * col2.b,
            col1.a * p + col2.a * (1 - p)};
    }
    
    inline std::ostream& operator<<(std::ostream& os, const color4f& col)
    {
        os << "color4f(r=" << col.r << ", g=" << col.g << ", b=" << col.b << ", a=" << col.a << ')';
        return os;
    }
    
    inline std::istream& operator>>(std::istream& is, color4f& col)
    {
        double r, g, b;
        if (is >> r && is >> g && is >> b) {
            col.r = r;
            col.g = g;
            col.b = b;
        }
        return is;
    }
}

#endif
