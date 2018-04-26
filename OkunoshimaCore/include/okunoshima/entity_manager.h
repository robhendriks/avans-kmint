#ifndef entity_manager_h
#define entity_manager_h

#include <vector>
#include <map>
#include "graphics.h"
#include "entity.h"
#include "texture_manager.h"
#include "random_utils.h"

#include "human_male.h"
#include "human_female.h"
#include "dog.h"
#include "rabbit.h"
#include "timer.h"
#include "genetic_algorithm.h"
#include "input.h"
#include "keyboard_listener.h"

namespace okunoshima
{
    constexpr static const int AGENT_UPDATE_INTERVAL = 10;
    
    struct nearby_agent
    {
        rabbit* agent;
        double distance;
        
        nearby_agent(rabbit* agent, double distance) : agent{agent}, distance{distance} {}
    };
    
    class world;
    class entity_manager : public keyboard_listener
    {
        world& m_world;
        std::vector<entity*> m_entities;
        std::vector<rabbit*> m_agents;
        std::vector<rabbit*> m_dead_agents;
        std::vector<rabbit*> m_selection;
        timer m_agent_timer;
        genetic_algorithm m_genetic_algorithm;
        bool m_debug_draw;
    public:
        entity_manager(world& w) : m_world{w}, m_entities{} , m_agents{}, m_genetic_algorithm{}, m_debug_draw{false}
        {
            input::get_instance().get_keyboard().add_listener(*this);
        }
        
        ~entity_manager()
        {
            input::get_instance().get_keyboard().remove_listener(*this);
        }
        
        void load();
        void reset();
        void cleanup();
        void update();
        void update_agents();
        void draw(graphics& g);
        void handle(const keyboard::event& e) override;
        void spawn();
        void spawn_agents();
        
        dog* find_dog() const;
        human* find_human(human_type type) const;
        
        bool agents_in_radius(entity& e, double radius) const;
        std::vector<nearby_agent> get_agents_in_radius(entity& e, double radius) const;
        rabbit* nearest_agent_in_radius(entity& e, double radius) const;
        
        world& get_world() { return m_world; }
        const world& get_world() const { return m_world; }
        
        std::vector<entity*>& get_entities() { return m_entities; }
        const std::vector<entity*>& get_entities() const { return m_entities; }
        
        std::vector<rabbit*>& get_agents() { return m_agents; }
        const std::vector<rabbit*>& get_agents() const { return m_agents; }
    };
}

#endif

