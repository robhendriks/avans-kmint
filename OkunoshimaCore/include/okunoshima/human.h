#ifndef human_h
#define human_h

#include "entity.h"

namespace okunoshima
{
    enum human_type
    {
        MALE,
        FEMALE
    };
    
    class human : public entity
    {
        human_type m_type;
    public:
        human(const std::string& name, world* w, human_type type) : entity{name, w}, m_type{type} {}
        
        human_type get_type() const { return m_type; }
    };
}

#endif

