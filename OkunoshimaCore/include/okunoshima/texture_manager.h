#ifndef texture_manager_h
#define texture_manager_h

#include <map>
#include <memory>
#include "graphics.h"
#include "texture.h"
#include "sprite.h"

namespace okunoshima
{
    using texture_ptr = std::shared_ptr<texture>;
    using sprite_ptr = std::shared_ptr<sprite>;
    
    class texture_manager
    {
        static texture_manager* s_instance;
        std::map<std::string, texture_ptr> m_textures;
    public:
        texture_manager();
        ~texture_manager();
        texture_manager(const texture_manager&) = delete;
        texture_manager& operator=(const texture_manager&) = delete;
        
        static texture_manager* get_instance()
        {
            if (s_instance == 0) {
                s_instance = new texture_manager();
                return s_instance;
            }
            return s_instance;
        }
        
        texture_ptr load(graphics& g, const std::string& file_name);
        sprite_ptr load_sprite(graphics& g, const std::string& file_name);
        
        void destroy();
    };
}

#endif
