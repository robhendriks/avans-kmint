#include "gene_map.h"
#include "random_utils.h"
#include "logger.h"

namespace okunoshima
{
    void gene_map::fill(std::initializer_list<gene> il)
    {
        for (auto& g : il) {
            m_genes.emplace(g.get_name(), g);
        }
    }
    
    void gene_map::crossover(const gene_map& other)
    {
        // Get all keys
        std::vector<const std::string> keys;
        keys.reserve(m_genes.size());
        for (auto& pair : m_genes) { keys.push_back(pair.first); }
        
        // Determine center point
        randomizer r{0, static_cast<int>(keys.size() - 1)};
        int center = r.random();
        
        // Keep genes on the left of the center point and replace
        // genes on the right with the other parent's genes
        for (int i = 0; i < keys.size(); ++i) {
            auto key = keys.at(i);
            if (i <= center) { continue;}
            set_value(key, other.get_value(key));
        }
    }
    
    void gene_map::mutate(int rate)
    {
        // Get all keys
        std::vector<const std::string> keys;
        keys.reserve(m_genes.size());
        for (auto& pair : m_genes) { keys.push_back(pair.first); }
        
        randomizer r{0, 100};
        
        // Rate to 100 chance of a random mutation for each gene
        for (int i = 0; i < keys.size(); ++i) {
            if (r.random() >= rate) { continue; }
            
            auto key = keys.at(i);
            get(key).randomize();
        }
    }
    
    void gene_map::print() const
    {
        std::cout << (*this) << std::endl;
    }
    
    gene& gene_map::get(const std::string& key)
    {
        auto it = m_genes.find(key);
        if (it == m_genes.end()) {
            throw std::out_of_range{"error - gene not found: " + key};
        }
        return it->second;
    }
    
    double gene_map::get_value(const std::string& key) const
    {
        auto it = m_genes.find(key);
        if (it == m_genes.end()) {
            throw std::out_of_range{"error - gene not found: " + key};
        }
        return it->second.get_value();
    }
    
    void gene_map::set_value(const std::string& key, double value)
    {
        auto it = m_genes.find(key);
        if (it == m_genes.end()) {
            throw std::out_of_range{"error - gene not found: " + key};
        }
        it->second.set_value(value);
    }
}
