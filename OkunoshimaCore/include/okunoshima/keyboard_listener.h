#ifndef keyboard_listener_h
#define keyboard_listener_h

#include "keyboard.h"

namespace okunoshima
{
    class keyboard_listener
    {
    public:
        virtual void handle(const keyboard::event& e) = 0;
    };
}

#endif
