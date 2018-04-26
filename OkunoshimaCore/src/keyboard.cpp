#include "keyboard.h"
#include "keyboard_listener.h"

namespace okunoshima
{
    void keyboard::handle_key_down(const int32_t key_code)
    {
        notify_listeners({event::DOWN, key_code, SDL_GetKeyName(key_code)});
        
        auto it = m_keys.find(key_code);
        if (it != m_keys.end()) { return; }
        m_keys.emplace(key_code, SDL_GetTicks());
    }
    
    void keyboard::handle_key_up(const int32_t key_code)
    {
        notify_listeners({event::UP, key_code, SDL_GetKeyName(key_code)});
        
        auto it = m_keys.find(key_code);
        if (it == m_keys.end()) { return; }
        m_keys.erase(it);
        
        uint32_t now = SDL_GetTicks();
        uint32_t duration = now - it->second;
        
        notify_listeners({event::PRESSED, key_code, SDL_GetKeyName(key_code), duration});
    }
    
    void keyboard::update(SDL_Event& e)
    {
        switch (e.type) {
            case SDL_KEYDOWN:
                handle_key_down(e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                handle_key_up(e.key.keysym.sym);
                break;
            default:
                break;
        }
    }
    
    void keyboard::add_listener(okunoshima::keyboard_listener &listener)
    {
        std::lock_guard<std::mutex>{m_listeners_mutex};
        
        auto it = std::find(m_listeners.begin(), m_listeners.end(), &listener);
        if (it == m_listeners.end()) {
            m_listeners.push_back(&listener);
        }
    }
    
    void keyboard::remove_listener(okunoshima::keyboard_listener &listener)
    {
        std::lock_guard<std::mutex>{m_listeners_mutex};
        
        auto it = std::find(m_listeners.begin(), m_listeners.end(), &listener);
        if (it != m_listeners.end()) {
            m_listeners.erase(it);
        }
    }
    
    void keyboard::notify_listeners(const event& e)
    {
        std::lock_guard<std::mutex>{m_listeners_mutex};
        
        for (auto listener : m_listeners) {
            listener->handle(e);
        }
    }
}
