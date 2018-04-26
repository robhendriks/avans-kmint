#ifndef genetic_entity_h
#define genetic_entity_h

#include <iostream>
#include "gene_map.h"
#include "timer.h"

namespace okunoshima
{
    class genetic_entity
    {
        bool m_alive;
        timer m_alive_timer;
        uint32_t m_alive_ticks;
        gene_map m_genes;
        double m_fitness = 0;
        
        void init();
        
    public:
        genetic_entity(const genetic_entity& ge) : genetic_entity{ge.m_genes}
        {
            m_alive = ge.m_alive;
            m_alive_ticks = ge.m_alive_ticks;
        }
        
        genetic_entity(const gene_map& genes) : m_alive{true}, m_alive_ticks{0}, m_genes{genes} { init(); }
        
        void print() const;
        void kill();
        
        genetic_entity& operator=(const genetic_entity& ge)
        {
            if (this != &ge) {
                m_alive = ge.m_alive;
                m_alive_ticks = ge.m_alive_ticks;
                m_genes = ge.m_genes;
            }
            return *this;
        }
        
        bool is_alive() const { return m_alive; }
        uint32_t get_alive_ticks() const { return m_alive_ticks; }
        
        double get_cohesion() const { return m_genes.get_value("cohesion"); };
        void set_cohesion(double value) { m_genes["cohesion"] = value; }
        
        double get_separation() const { return m_genes.get_value("separation"); };
        void set_separation(double value) { m_genes["separation"] = value; }
        
        double get_alignment() const { return m_genes.get_value("alignment"); };
        void set_alignment(double value) { m_genes["alignment"] = value; }
        
        double get_water_attraction() const { return m_genes.get_value("water_attraction"); };
        void set_water_attraction(double value) { m_genes["water_attraction"] = value; }
        
        double get_dog_attraction() const { return m_genes.get_value("dog_attraction"); };
        void set_dog_attraction(double value) { m_genes["dog_attraction"] = value; }
        
        gene_map& get_genes() { return m_genes; }
        const gene_map& get_genes() const { return m_genes; }
        void set_genes(const gene_map& genes) { m_genes = genes; }
        
        double get_fitness() const { return m_fitness; }
        void set_fitness(double fitness) { m_fitness = fitness; }
        
        friend std::ostream& operator<<(std::ostream& os, const genetic_entity& ge);
    };
    
    inline std::ostream& operator<<(std::ostream& os, const genetic_entity& ge)
    {
        os  << "{alive=" << std::boolalpha << ge.m_alive << std::noboolalpha
            << ", alive_ticks=" << ge.m_alive_ticks
            << ", genes=" << ge.m_genes << '}';
        return os;
    }
}

#endif
