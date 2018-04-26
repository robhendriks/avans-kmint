#include "window.h"
#include "logger.h"

namespace okunoshima
{
    window::window(const window_config& config) : m_config{config}, m_window{nullptr}, m_size{}, m_fullscreen{false}
    {
        logger::info("window::window()");
        init();
    }
    
    window::~window()
    {
        logger::info("window::~window()");
        
        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }
    
    void window::init()
    {
        if (!(m_window = SDL_CreateWindow(m_config.title.c_str(), m_config.x, m_config.y, m_config.w, m_config.h, m_config.flags))) {
            throw std::runtime_error(SDL_GetError());
        }
        get_actual_size();
    }
    
    void window::update(const SDL_Event& event)
    {
        // Handle window resize event
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            get_actual_size();
        }
    }
    
    void window::get_actual_size()
    {
        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        
        m_size.x = w;
        m_size.y = h;
    }
    
    SDL_Window* window::get_window()
    {
        return m_window;
    }
    
    const SDL_Window* window::get_window() const
    {
        return m_window;
    }
    
    vector2d& window::get_size()
    {
        return m_size;
    }
    
    const vector2d& window::get_size() const
    {
        return m_size;
    }
    
    void window::fullscreen()
    {
        m_fullscreen = !m_fullscreen;
        uint32_t flags = m_fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
        SDL_SetWindowFullscreen(m_window, flags);
    }
}
