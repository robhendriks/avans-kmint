#include "dog_state_find_human.h"
#include "dog_state_wander.h"
#include "dog_state_find_cave.h"
#include "world.h"
#include "logger.h"

namespace okunoshima
{
    void dog_state_find_human::check_state()
    {
        if (m_dog.get_thirst() < MAX_THIRST) {
            if (m_dog.get_drink_count() >= 2) {
                m_dog.set_state(std::make_shared<dog_state_find_cave>(m_dog));
            } else {
                m_dog.set_state(std::make_shared<dog_state_wander>(m_dog));
            }
        }
    }
    
    void dog_state_find_human::update()
    {
        auto& w = m_dog.get_world();
        
        randomizer index{0, 100};
        
        if (m_target && m_target->get_current_node()->get_id() == m_dog.get_current_node()->get_id()) {
            logger::info("OK LOL");
            
            int min_thirst = 0;
            
            if(m_target->get_type() == MALE){
                randomizer mt{30, 50};
                min_thirst = mt.random();
                
                if(m_dog.get_last_drink_amount() < min_thirst){
                    m_dog.set_last_drink_amount(min_thirst);
                    if(m_dog.get_drink_change() > 5){
                        m_dog.set_drink_change(m_dog.get_drink_change() - 5);
                    }
                }
            }else{
                randomizer ft{10, 80};
                min_thirst = ft.random();
                
                if(m_dog.get_last_drink_amount() < min_thirst){
                    m_dog.set_last_drink_amount(min_thirst);
                    if(m_dog.get_drink_change() < 95){
                        m_dog.set_drink_change(m_dog.get_drink_change() + 5);
                    }
                }
            }
            
            m_dog.set_thirst(m_dog.get_thirst() - min_thirst);
            
            logger::info("Thirst -" + std::to_string(min_thirst));
            logger::info("Thirst change = " + std::to_string(m_dog.get_drink_change()));
            
            m_dog.set_drink_count(m_dog.get_drink_count() + 1);

        } else if (!m_target) {
            m_target = w.find_human(index.random() >= m_dog.get_drink_change() ? MALE : FEMALE); // CHANCE
            
            if (m_target) {
                if (auto node = m_target->get_current_node()) {
                    update_target_position(node);
                    update();
                }
            } else {
//                std::cout << "<dog> no target!" << std::endl;
            }
        } else {
            if (auto node = m_target->get_current_node()) {
                if (m_target_position != node->get_position()) {
                    update_target_position(node);
                    update();
                } else if(!m_target_path.empty()) {
//                    std::cout << "<dog> going to human" << std::endl;
                    
                    m_dog.set_current_node(m_target_path.front());
                    m_target_path.erase(m_target_path.begin());
                }
            } else {
                throw std::runtime_error{"error - dog has no target"};
            }
        }
        
    }
    
    void dog_state_find_human::draw(graphics& g)
    {
        if (!m_target_path.empty()) {
            g.draw_path(colors::orange, m_target_path);
        }
    }
    
    void dog_state_find_human::update_target_position(node* target)
    {
        auto& w = m_dog.get_world();
        
        m_target_position = target->get_position();
        
        path_finding pf{w.get_graph()};
        if (pf.find(m_dog.get_current_node(), target)) {
            m_target_path = pf.get_path();
            logger::info("Dog found path to human");
        } else {
            m_target_path.clear();
            logger::warn("Dog could not determine path to human");
        }
    }
    
    std::string dog_state_find_human::get_name() const
    {
        if (!m_target) { return dog_state::get_name(); }
        return dog_state::get_name() + '(' + m_target->get_name() + ')';
    }
}

