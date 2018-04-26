#include "engine.h"
#include "component.h"
#include "logger.h"

namespace okunoshima
{
    engine::engine(const engine_config& config) : m_config{config}, m_window{nullptr}, m_graphics{nullptr}, m_quit{false}, m_paused{false}
    {        
        logger::info("engine::engine()");
        input::get_instance().get_keyboard().add_listener(*this);
    }
    
    engine::~engine()
    {
        logger::info("engine::~engine()");
        input::get_instance().get_keyboard().remove_listener(*this);
    }
    
    void engine::init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(SDL_GetError());
        }
        
        int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
        if ((IMG_Init(img_flags) & img_flags) != img_flags) {
            throw std::runtime_error(IMG_GetError());
        }
        
        try {
            m_window = std::make_unique<window>(m_config.window);
            m_graphics = std::make_unique<graphics>(*m_window);
        } catch (std::exception& e) {
            //
        }
        
        m_graphics->set_clear_color(m_config.clear_color);
        
        for (auto& component : m_components) {
            component.second->load();
        }
        
        loop();
    }
    
    void engine::loop()
    {
        while (!m_quit) {
            update();
            render();
        }
        
        cleanup();
    }
    
    void engine::update()
    {
        auto& kb = input::get_instance().get_keyboard();
        
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                m_quit = true;
                break;
            } else if (e.type == SDL_WINDOWEVENT) {
                m_window->update(e);
            }
            
            kb.update(e);
        }
        
        if (m_paused) { return; }
        
        for (auto& component : m_components) {
            component.second->update();
        }
    }
    
    void engine::render()
    {
        m_graphics->clear();
    
        for (auto& component : m_components) {
            component.second->draw(*m_graphics);
        }
        
        if (m_paused) {
            m_graphics->fill_rect({255, 255, 255, 255}, {10, 10, 20, 40});
            m_graphics->fill_rect({255, 255, 255, 255}, {30, 10, 40, 40});
        }
        
        m_graphics->display();
    }
    
    void engine::handle(const keyboard::event& e)
    {
        if (e.type != keyboard::event::PRESSED) { return; }
        
        if (e.key_code == SDLK_p) {
            m_paused = !m_paused;
        }
        
        if (e.key_code == SDLK_f) {
            m_window->fullscreen();
        }
    }
    
    void engine::cleanup()
    {
        auto tm = texture_manager::get_instance();
        tm->destroy();
        
        m_graphics = nullptr;
        m_window = nullptr;
        
        IMG_Quit();
        SDL_Quit();
    }
}
