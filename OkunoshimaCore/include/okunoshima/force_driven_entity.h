#ifndef force_driven_entity_h
#define force_driven_entity_h

#include "entity.h"
#include "vector2d.h"
#include "genetic_entity.h"

namespace okunoshima
{
    constexpr static const int D = 200;
    
    class rabbit;
    class force_driven_entity : public entity, public genetic_entity
    {
        void apply_behaviours();
    protected:
        double m_mass, m_max_speed, m_max_force;
        
        std::vector<node*> m_current_nodes;
        vector2d m_force;
        vector2d m_acceleration;
        vector2d m_velocity;
        vector2d m_position;
        
        bool add_node(node* n)
        {
            auto it = std::find(m_current_nodes.begin(), m_current_nodes.end(), n);
            if (it == m_current_nodes.end()) {
                m_current_nodes.push_back(n);
                return true;
            }
            return false;
        }
        
        bool remove_node(node* n)
        {
            auto it = std::find(m_current_nodes.begin(), m_current_nodes.end(), n);
            if (it != m_current_nodes.end()) {
                m_current_nodes.erase(it);
                return true;
            }
            return false;
        }
        
    public:
        force_driven_entity(const std::string& name, world* w, const gene_map& genes, double mass, double max_speed, double max_force);
        
        void seek(const vector2d& target, double weight);
        void seek_with_distance(const vector2d& target, double max_distance, double weight);
        void align();
        void separate();
        void cohere();
        
        void apply_force(const vector2d& force, double weight);
        
        void update() override;
        void draw(graphics& g) override;
        
        vector2d& get_force();
        void set_force(const vector2d& force);
        const vector2d& get_acceleration() const;
        const vector2d& get_velocity() const;
        vector2d& get_position();
        void set_position(const vector2d& position);
        
        rect2d get_bounds() const
        {
            vector2d size{20, 20};
            return {m_position - size / 2, m_position + size / 2};
        }
        
        size_t number_of_nodes() const { return m_current_nodes.size(); }
    };
}

#endif
