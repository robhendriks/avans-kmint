#include "sprite.h"
#include "graphics.h"
#include "logger.h"

namespace okunoshima
{
    void sprite::load(graphics &ctx, const std::string &file_name)
    {
        texture::load(ctx, file_name);
        if (!is_loaded()) { return; }
        
        auto size = get_size();
        
        int w = static_cast<int>(size.x);
        int h = static_cast<int>(size.y);
        
        if (h % w != 0) {
            throw std::runtime_error{"invalid sprite dimensions"};
        }
        
        m_frame_count = h / w;
    }
    
    rect2d sprite::get_frame(int frame_number) const
    {
        if (frame_number > m_frame_count - 1) {
            throw std::invalid_argument{"invalid frame number"};
        }
        
        vector2d size = get_size();
        vector2d frame_size{size.x, size.x};
        vector2d frame_position{0, frame_size.y * frame_number};
        
        return {frame_position, frame_position + frame_size };
    }
}
