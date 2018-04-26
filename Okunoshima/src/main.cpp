#include <iostream>
#include <okunoshima/engine.h>
#include <okunoshima/world.h>

using namespace okunoshima;

int main(int argc, const char* argv[]) {
    engine_config cfg{
        colors::blue,
        {
            "Okunoshima",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280,
            720,
            SDL_WINDOW_SHOWN
        }
    };
    
    engine e{cfg};
    world w{e};
    
    e.init();
    
    return 0;
}
