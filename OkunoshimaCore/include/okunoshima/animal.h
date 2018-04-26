#ifndef animal_h
#define animal_h

#include "entity.h"

namespace okunoshima
{
    class animal : public entity
    {
    public:
        animal(const std::string& name, world* w) : entity{name, w} {}
    };
}

#endif

