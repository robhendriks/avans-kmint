#ifndef gene_h
#define gene_h

#include <iostream>
#include <string>
#include <map>

namespace okunoshima
{
    class gene
    {
        std::string m_name;
        double m_value;
        double m_lo_value;
        double m_hi_value;
    public:
        gene(const std::string& name, double value, double lo_value, double hi_value) : m_name{name} , m_value{value}, m_lo_value{lo_value}, m_hi_value{hi_value} {}
        
        gene(const gene& g) : gene{g.m_name, g.m_value, g.m_lo_value, g.m_hi_value} {}
        
        gene& operator=(const gene& g)
        {
            if (this != &g) {
                m_name = g.m_name;
                m_value = g.m_value;
                m_lo_value = g.m_lo_value;
                m_hi_value = g.m_hi_value;
            }
            return *this;
        }
        
        void operator=(double value) { set_value(value); }
        
        void randomize();
        void print() const;
        
        operator double() const { return m_value; }
        
        double get_value() const { return m_value; }
        void set_value(double value) { m_value = std::clamp(value, m_lo_value, m_hi_value); }
        double get_lo_value() const { return m_lo_value; }
        double get_hi_value() const { return m_hi_value; }
        
        std::string get_name() const { return m_name; }
        
        friend std::ostream& operator<<(std::ostream& os, const gene& g);
    };
    
    inline std::ostream& operator<<(std::ostream& os, const gene& g)
    {
        os << "{name=" << g.m_name << ", value=" << g.m_value << '}';
        return os;
    }
}

#endif
