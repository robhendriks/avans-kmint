#ifndef input_h
#define input_h

#include "keyboard.h"

namespace okunoshima
{
    class input
    {
        keyboard m_keyboard;
    public:
        input() = default;
        input(const input&) = delete;
        input& operator=(const input&) = delete;
        
        static input& get_instance()
        {
            static input instance;
            return instance;
        }
        
        keyboard& get_keyboard() { return m_keyboard; }
    };
}

#endif
