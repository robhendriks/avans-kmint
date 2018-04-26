#ifndef gene_map_h
#define gene_map_h

#include <iostream>
#include <vector>
#include <unordered_map>
#include "gene.h"

namespace okunoshima
{
    class gene_map
    {
        std::unordered_map<std::string, gene> m_genes;
        
        void fill(std::initializer_list<gene> il);
        
    public:
        gene_map() {}
        gene_map(const gene_map& gm) : m_genes{gm.m_genes} {}
        gene_map(std::initializer_list<gene> il) { fill(il); }
        
        gene_map& operator=(const gene_map& gm)
        {
            if (this != &gm) {
                m_genes = gm.m_genes;
            }
            return *this;
        }
        
        gene_map& operator+=(const gene_map& other)
        {
            crossover(other);
            return *this;
        }
        
        void crossover(const gene_map& other);
        void mutate(int rate);
        void print() const;
        
        decltype(auto) begin() { return m_genes.begin(); }
        decltype(auto) begin() const { return m_genes.begin(); }
        decltype(auto) end() { return m_genes.end(); }
        decltype(auto) end() const { return m_genes.end(); }
        decltype(auto) size() const { return m_genes.size(); }
        
        gene& operator[](const std::string& key) { return get(key); }
        
        gene& get(const std::string& key);
        double get_value(const std::string& key) const;
        void set_value(const std::string& key, double value);
        
        friend std::ostream& operator<<(std::ostream& os, const gene_map& gm);
    };
    
    inline gene_map operator+(gene_map lhs, const gene_map& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    
    inline std::ostream& operator<<(std::ostream& os, const gene_map& gm)
    {
        os << '{' << std::endl;
        
        for (auto& g : gm.m_genes) {
            os << '\t' << g.second << std::endl;
        }
        
        os << '}';
        
        return os;
    }
}

#endif
