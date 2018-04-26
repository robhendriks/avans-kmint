#include "entity_manager.h"
#include "world.h"
#include "dog_state_wander.h"
#include "human_male_state_wander.h"
#include "human_female_state_wander.h"
#include "logger.h"

namespace okunoshima
{
    void entity_manager::spawn()
    {
        auto& spawn_nodes = m_world.get_graph().get_spawn_nodes();
        
        // Male
        human_male* male = new human_male{&m_world};
        male->set_current_node(std::get<1>(spawn_nodes["male"]));
        male->set_state(std::make_shared<human_male_state_wander>(*male));
        
        // Female
        human_female* female = new human_female{&m_world};
        female->set_current_node(std::get<1>(spawn_nodes["female"]));
        female->set_state(std::make_shared<human_female_state_wander>(*female));
        
        // Dog
        dog* snoop_d_o_double_g = new dog{&m_world};
        snoop_d_o_double_g->set_current_node(std::get<1>(spawn_nodes["dog"]));
        snoop_d_o_double_g->set_state(std::make_shared<dog_state_wander>(*snoop_d_o_double_g));
        
        m_entities.push_back(male);
        m_entities.push_back(female);
        m_entities.push_back(snoop_d_o_double_g);
    }
    
    void entity_manager::load()
    {        
        spawn();
        reset();
    }
    
    void entity_manager::reset()
    {
        if (auto dog = find_dog()) {
            dog->set_drink_count(0);
            dog->set_thirst(0);
        }
        
        cleanup();
        spawn_agents();
    }
    
    void entity_manager::cleanup()
    {
        m_selection.insert(m_selection.end(), m_agents.begin(), m_agents.end());
        m_selection.insert(m_selection.end(), m_dead_agents.begin(), m_dead_agents.end());
        m_genetic_algorithm.gather_parents(m_selection);
        m_selection.clear();
        
        auto& g = m_world.get_graph();
        for (auto& n : g) {
            n.clear_agents();
        }
        
        std::for_each(m_dead_agents.begin(), m_dead_agents.end(), std::default_delete<rabbit>());
        m_dead_agents.clear();
        
        std::for_each(m_agents.begin(), m_agents.end(), std::default_delete<rabbit>());
        m_agents.clear();
    }
    
    void entity_manager::spawn_agents()
    {
        randomizer rx{0, 1280};
        randomizer ry{0, 720};
        
        auto& g = m_world.get_graph();
        auto& nodes = g.get_nodes();
        randomizer r{0, static_cast<int>(nodes.size() - 1)};
        
        gene_map default_genes{
            {"cohesion", 0.0, 0.0, 1.0},
            {"separation", 0.0, 0.0, 1.0},
            {"alignment", 0.0, 0.0, 1.0},
            {"water_attraction", 0.0, -1.0, 1.0},
            {"dog_attraction", 0.0, -1.0, 1.0}
        };
        
        for (int i = 0; i < 100; i++) {
            rabbit* agent = new rabbit{&m_world, i, default_genes};
            
            auto& node = nodes.at(r.random());
            agent->set_position(node.get_position());
            
            m_agents.push_back(std::move(agent));
        }
        
        m_genetic_algorithm.setup(m_agents);
    }
    
    void entity_manager::update()
    {
        for (auto e : m_entities) {
            e->update();
        }
        update_agents();
    }
    
    void entity_manager::update_agents()
    {
        if (!m_agent_timer.is_started()) { m_agent_timer.start(); }
        if (m_agent_timer.get_ticks() < AGENT_UPDATE_INTERVAL) { return; };

        m_agent_timer.stop();
        m_agent_timer.start();
        
        for (auto a : m_agents) {
            a->update();
        }
        
        for (auto a : m_agents) {
            if (a->number_of_nodes() == 0) {
                a->kill();
                logger::info(std::string("Agent #") + std::to_string(a->get_id()) + " was killed");
            }
            
            if (!a->is_alive()) {
                auto it = std::find(m_agents.begin(), m_agents.end(), a);
                if (it != m_agents.end()) {
                    m_agents.erase(it);
                    m_dead_agents.push_back(a);
                }
                
                logger::info(std::string("Remaining agents: ") + std::to_string(m_agents.size()));
            }
        }
    }
    
    void entity_manager::draw(graphics& g)
    {
        for (auto e : m_entities) {
            e->draw(g);
        }
        for (auto a : m_agents) {
            a->draw(g);
            
            if (!m_debug_draw) { continue; }
            
            if (auto n = a->get_current_node()) {
                g.set_color(colors::brown);
                g.draw_rect(n->get_bounds());
            }
            
            int i = 0;
            for (auto& pair : a->get_genes()) {
                auto& gn = pair.second;
                
                progress_bar pb{{25, 3}, gn.get_lo_value(), gn.get_hi_value(), gn.get_value()};
                pb.set_foreground(lighten(colors::brown, 10));
                pb.set_background(darken(colors::brown, 10));
                
                auto pos = a->get_position() - vector2d{0, 12 + 9 * static_cast<double>(i)};
                pb.draw_at(pos, g);
                
                auto c = gn.get_name().at(0);
                g.draw_string(pos - vector2d{15, 0}, std::string(1, c), align_right | align_middle);
                
                ++i;
            }
        }
    }
    
    void entity_manager::handle(const keyboard::event &e)
    {
        if (e.type != keyboard::event::PRESSED) { return; }
        
        if (e.key_code == SDLK_e) {
            m_debug_draw = !m_debug_draw;
        }
    }
    
    dog* entity_manager::find_dog() const
    {
        auto it = std::find_if(m_entities.begin(), m_entities.end(), [](entity* e) {
            return dynamic_cast<dog*>(e);
        });
        return it != m_entities.end() ? dynamic_cast<dog*>(*it) : nullptr;
    }
    
    human* entity_manager::find_human(human_type type) const
    {
        auto it = std::find_if(m_entities.begin(), m_entities.end(), [type](entity* e) {
            if (auto h = dynamic_cast<human*>(e)) {
                return h->get_type() == type;
            }
            return false;
        });
        return it != m_entities.end() ? dynamic_cast<human*>(*it) : nullptr;
    }
    
    bool entity_manager::agents_in_radius(entity& e, double radius) const
    {
        auto node = e.get_current_node();
        if (!node) { return false; }
        
        for (auto a : m_agents) {
            if (distance(a->get_position(), node->get_position()) <= radius) {
                return true;
            }
        }
        return false;
    }
    
    std::vector<nearby_agent> entity_manager::get_agents_in_radius(entity& e, double radius) const
    {
        std::vector<nearby_agent> agents;
        
        auto node = e.get_current_node();
        if (!node) { return agents; }
        
        for (auto a : m_agents) {
            double dist = distance(a->get_position(), node->get_position());
            if (dist <= radius) {
                agents.emplace_back(a, dist);
            }
        }
        
        if (agents.empty()) { return agents; }
        
        std::sort(agents.begin(), agents.end(), [](const nearby_agent& a, const nearby_agent& b) {
            return a.distance < b.distance;
        });
        
        return agents;
    }
    
    rabbit* entity_manager::nearest_agent_in_radius(entity& e, double radius) const
    {
        auto node = e.get_current_node();
        if (!node) { return nullptr; }
        
        rabbit* agent = nullptr;
        double min_distance = std::numeric_limits<double>::max();
        
        for (auto a : m_agents) {
            double dist = distance(a->get_position(), node->get_position());
            if (dist <= radius && dist < min_distance) {
                agent = a;
            }
        }
        
        return agent;
    }
}

