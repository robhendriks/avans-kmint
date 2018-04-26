#ifndef engine_h
#define engine_h

#include <memory>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "graphics.h"
#include "color4f.h"
#include "rect2d.h"
#include "texture_manager.h"
#include "colors.h"
#include "input.h"
#include "keyboard_listener.h"

namespace okunoshima
{
    struct engine_config
    {
        color4f clear_color;
        window_config window;
    };
    
    class component;
    class engine : public keyboard_listener
    {
        friend class component;
        
        std::unordered_map<std::string, component*> m_components;
        const engine_config m_config;
        std::unique_ptr<window> m_window;
        std::unique_ptr<graphics> m_graphics;
        bool m_quit;
        bool m_paused;
        
        void loop();
        void update();
        void render();
        void handle(const keyboard::event& e) override;
        void cleanup();
        
    public:
        engine(const engine_config& config);
        ~engine();
        
        window& get_window() const { return *m_window; }
        graphics& get_graphics() const { return *m_graphics; }
        
        void init();
    };
}

#endif
