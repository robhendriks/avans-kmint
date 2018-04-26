#ifndef window_h
#define window_h

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "vector2d.h"

namespace okunoshima {
    struct window_config
    {
        std::string title;
        int x, y, w, h;
        uint32_t flags;
    };
    
    class window
    {
        const window_config m_config;
        SDL_Window *m_window;
        vector2d m_size;
        bool m_fullscreen;
        
        void init();
        void get_actual_size();
        
    public:
        window(const window_config& config);
        ~window();
        
        void fullscreen();
        void update(const SDL_Event& event);
        
        SDL_Window* get_window();
        const SDL_Window* get_window() const;
        vector2d& get_size();
        const vector2d& get_size() const;
    };
}

#endif
