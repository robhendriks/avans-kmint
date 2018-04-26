#include "texture_manager.h"

namespace okunoshima
{
    texture_manager* texture_manager::s_instance;
    
    texture_manager::texture_manager()
    {
    }
    
    texture_ptr texture_manager::load(graphics& g, const std::string& file_name)
    {
        auto it = m_textures.find(file_name);
        if (it != m_textures.end()) {
            return it->second;
        }
        
        texture_ptr t = std::make_shared<texture>();
        t->load(g, file_name);
        
        m_textures.emplace(file_name, t);
        
        return t;
    }
    
    sprite_ptr texture_manager::load_sprite(graphics& g, const std::string& file_name)
    {
        auto it = m_textures.find(file_name);
        if (it != m_textures.end()) {
            auto s_ptr = std::dynamic_pointer_cast<sprite>(it->second);
            if (!s_ptr) {
                throw std::runtime_error{"not a sprite"};
            }
            return s_ptr;
        }
        
        sprite_ptr t = std::make_shared<sprite>();
        t->load(g, file_name);
        
        m_textures.emplace(file_name, t);
        
        return t;
    }
    
    void texture_manager::destroy()
    {
        m_textures.clear();
    }
}
