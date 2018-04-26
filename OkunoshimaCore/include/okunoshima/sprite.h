#ifndef sprite_h
#define sprite_h

#include "texture.h"
#include "rect2d.h"

namespace okunoshima
{
    class sprite : public texture
    {
        int m_frame_count;
    public:
        sprite() : texture{}, m_frame_count{0} {}
        
        void load(graphics &ctx, const std::string &file_name) override;
        
        int get_frame_count() const { return m_frame_count; }
        rect2d get_frame(int frame_number) const;
    };
}

#endif
