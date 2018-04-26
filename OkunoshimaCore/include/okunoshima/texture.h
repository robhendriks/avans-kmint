#ifndef texture_h
#define texture_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vector2d.h"

namespace okunoshima
{
    class graphics;
    
    class texture
    {
        bool m_loaded;
        SDL_Texture* m_texture;
        vector2d m_size;
    public:
        texture();
        ~texture();
        
        virtual void load(graphics& ctx, const std::string& file_name);
        bool is_loaded() const;
        
        SDL_Texture* get_texture() const;
        vector2d& get_size();
        const vector2d& get_size() const;
    };
}

#endif
