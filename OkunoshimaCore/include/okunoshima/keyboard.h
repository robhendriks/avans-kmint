#ifndef keyboard_h
#define keyboard_h

#include <vector>
#include <map>
#include <mutex>
#include <SDL2/SDL.h>

namespace okunoshima
{
    class keyboard_listener;
    class keyboard
    {
        std::vector<keyboard_listener*> m_listeners;
        std::mutex m_listeners_mutex;
        std::map<int32_t, uint32_t> m_keys;
        
        void handle_key_down(const int32_t key_code);
        void handle_key_up(const int32_t key_code);
        
    public:
        struct event
        {
            const enum event_type
            {
                UP,
                DOWN,
                PRESSED
            } type;
            
            const int32_t key_code;
            const char* key_name;
            const uint32_t duration;
        };
        
        keyboard() = default;
        ~keyboard() = default;
        
        void update(SDL_Event& e);
        
        void add_listener(keyboard_listener& listener);
        void remove_listener(keyboard_listener& listener);
        void notify_listeners(const event& e);
    };
}

#endif
