#include "force_driven_entity.h"
#include "rabbit.h"
#include "world.h"

namespace okunoshima
{
    force_driven_entity::force_driven_entity(const std::string& name, world* w, const gene_map& genes, double mass, double max_speed, double max_force) : entity{name, w}, genetic_entity{genes}, m_mass{mass}, m_max_speed{max_speed}, m_max_force{max_force}, m_force{}, m_acceleration{}, m_velocity{}, m_position{}
    {
    }
    
    void force_driven_entity::seek(const vector2d& target, double weight)
    {
        vector2d desired = target - m_position;
        desired.set_magnitude(m_max_speed);
        
        vector2d steer = desired - m_velocity;
        steer.limit(m_max_force);
        
        apply_force(steer, weight);
    }
    
    void force_driven_entity::seek_with_distance(const vector2d& target, double max_distance, double weight)
    {
        if (distance(target, m_position) > max_distance) { return; }
        
        vector2d desired = target - m_position;
        desired.set_magnitude(m_max_speed);
        
        vector2d steer = desired - m_velocity;
        steer.limit(m_max_force);
        
        apply_force(steer, weight);
    }
    
    void force_driven_entity::align()
    {
        auto& em = get_world().get_entity_manager();
        
        double max_distance = 30;
        vector2d sum;
        int count = 0;
        
        for (auto rabbit : em.get_agents()) {
            double d = manhattan_distance(m_position, rabbit->get_position());
            if (d > 0 && d < max_distance) {
                sum += rabbit->get_velocity();
                ++count;
            }
        }
        
        if (count > 0) {
            sum /= static_cast<double>(count);
            sum.set_magnitude(m_max_speed);
            
            vector2d steer = sum - m_velocity;
            steer.limit(m_max_force);
            apply_force(steer, get_alignment());
        }
    }
    
    void force_driven_entity::separate()
    {
        auto& em = get_world().get_entity_manager();
        
        double max_distance = 30;
        vector2d sum;
        int count = 0;
        
        for (auto rabbit : em.get_agents()) {
            double d = manhattan_distance(m_position, rabbit->get_position());
            if (d > 0 && d < max_distance) {
                vector2d diff = m_position - rabbit->get_position();
                diff.normalize();
                diff /= d;
                
                sum += diff;
                ++count;
            }
        }
        
        if (count > 0) {
            sum /= static_cast<double>(count);
            sum.normalize();
            sum *= m_max_speed;
            
            vector2d steer = sum - m_velocity;
            steer.limit(m_max_force);
            apply_force(steer, get_separation());
        }
    }
    
    void force_driven_entity::cohere()
    {
        auto& em = get_world().get_entity_manager();
        
        double max_distance = 30;
        vector2d sum;
        int count = 0;
        
        for (auto rabbit : em.get_agents()) {
            double d = manhattan_distance(m_position, rabbit->get_position());
            if (d > 0 && d < max_distance) {
                sum += rabbit->get_position();
                ++count;
            }
        }
        
        if (count > 0) {
            sum /= static_cast<double>(count);
            sum.normalize();
            sum *= m_max_speed;
            
            vector2d steer = sum - m_position;
            steer.limit(m_max_force);
            apply_force(steer, get_cohesion());
        }
    }
    
    void force_driven_entity::apply_force(const vector2d& force, double weight)
    {
        m_acceleration += (force * weight) / m_mass;
    }
    
    void force_driven_entity::apply_behaviours()
    {
        if (auto dog = get_world().find_dog()) {
            seek_with_distance(dog->get_current_node()->get_position(), 60, get_dog_attraction());
        }
        
        if (!m_current_nodes.empty()) {
            auto n = m_current_nodes.front();
//            seek_with_distance(n->get_position(), 15, get_water_attraction() * -1);
            seek(n->get_position(), get_water_attraction() * -1);
        }
        
        cohere();
        separate();
        align();
    }
    
    void force_driven_entity::update()
    {
        apply_behaviours();
        
        m_velocity += m_acceleration;
        m_velocity.limit(m_max_speed);
        
        m_position += m_velocity;
        
        m_acceleration *= 0;
    }
    
    void force_driven_entity::draw(graphics& g)
    {
    }
    
    vector2d& force_driven_entity::get_force()
    {
        return m_force;
    }
    
    void force_driven_entity::set_force(const vector2d& force)
    {
        m_force = force;
    }
    
    const vector2d& force_driven_entity::get_acceleration() const
    {
        return m_acceleration;
    }
    
    const vector2d& force_driven_entity::get_velocity() const
    {
        return m_velocity;
    }
    
    vector2d& force_driven_entity::get_position()
    {
        return m_position;
    }
    
    void force_driven_entity::set_position(const vector2d& position)
    {
        m_position = position;
    }
}
