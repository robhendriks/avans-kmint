#include "texture.h"
#include "graphics.h"
#include "logger.h"

namespace okunoshima {
    texture::texture() : m_loaded{false}, m_texture{nullptr}, m_size{}
    {
        logger::info("texture::texture()");
    }
    
    texture::~texture()
    {
        logger::info("texture::~texture()");
        
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }
    
    void texture::load(graphics &ctx, const std::string &file_name)
    {
        if (m_loaded) {
            throw std::runtime_error("error - texture already loaded");
        }
        
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (!surface) {
            throw std::runtime_error(std::string("error - unable to load texture; ") + IMG_GetError());
        }
        
        m_texture = SDL_CreateTextureFromSurface(ctx.get_renderer(), surface);
        if (!m_texture) {
            throw std::runtime_error(std::string("error - unable to create texture; ") + SDL_GetError());
        }
        
        int w, h;
        if (SDL_QueryTexture(m_texture, NULL, NULL, &w, &h)) {
            throw std::runtime_error(std::string("error - unable to gather texture information; ") + SDL_GetError());
        }
        
        m_size.x = w;
        m_size.y = h;
        
        m_loaded = true;
    }
    
    bool texture::is_loaded() const
    {
        return m_loaded;
    }
    
    SDL_Texture* texture::get_texture() const
    {
        return m_texture;
    }
    
    vector2d& texture::get_size()
    {
        return m_size;
    }
    
    const vector2d& texture::get_size() const
    {
        return m_size;
    }
}
