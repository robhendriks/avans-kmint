#include "graphics.h"
#include "logger.h"
#include "texture_manager.h"

namespace okunoshima
{
    graphics::graphics(window& w) : m_window{w}, m_renderer{nullptr}, m_color{}, m_clear_color{}, m_font{FC_CreateFont()}
    {
        logger::info("graphics::graphics()");
        init();
    }
    
    graphics::~graphics()
    {
        logger::info("graphics::~graphics()");
        
        if (m_renderer) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
        if (m_font) {
            FC_FreeFont(m_font);
        }
    }
    
    void graphics::init()
    {
        auto window = m_window.get_window();
        
        if (!(m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
            throw std::runtime_error(SDL_GetError());
        }
        
        FC_LoadFont(m_font, m_renderer, "RobotoMono-Regular.ttf", 9.0, {255, 255, 255, 255}, TTF_STYLE_NORMAL);
    }
    
    void graphics::clear()
    {
        set_render_color(m_clear_color);
        SDL_RenderClear(m_renderer);
    }
    
    void graphics::display()
    {
        SDL_RenderPresent(m_renderer);
    }
    
    void graphics::draw_rect(const rect2d& rect) const
    {
        SDL_Rect sdl_rect = static_cast<SDL_Rect>(rect);
        SDL_RenderDrawRect(m_renderer, &sdl_rect);
    }
    
    void graphics::draw_rect(const color4f &color, const rect2d &rect)
    {
        set_color(color);
        draw_rect(rect);
    }
    
    void graphics::fill_rect(const rect2d& rect) const
    {
        SDL_Rect sdl_rect = static_cast<SDL_Rect>(rect);
        SDL_RenderFillRect(m_renderer, &sdl_rect);
    }
    
    void graphics::fill_rect(const color4f &color, const rect2d &rect)
    {
        set_color(color);
        fill_rect(rect);
    }
    
    void graphics::draw_line(const vector2d &p1, const vector2d &p2) const
    {
        SDL_RenderDrawLine(m_renderer, p1.x, p1.y, p2.x, p2.y);
    }
    
    void graphics::draw_line(const color4f &color, const vector2d &p1, const vector2d &p2)
    {
        set_color(color);
        draw_line(p1, p2);
    }
    
    void graphics::draw_texture(const texture& tex, const vector2d& vec) const
    {
        rect2d rect{vec, vec + tex.get_size()};
        SDL_Rect sdl_rect = static_cast<SDL_Rect>(rect);
        SDL_RenderCopy(m_renderer, tex.get_texture(), NULL, &sdl_rect);
    }
    
    void graphics::draw_texture(const texture& tex, const rect2d& rect) const
    {
        SDL_Rect sdl_rect = static_cast<SDL_Rect>(rect);
        SDL_RenderCopy(m_renderer, tex.get_texture(), NULL, &sdl_rect);
    }
    
    void graphics::draw_texture(const texture& tex, const rect2d& src, const rect2d& dst) const
    {
        SDL_Rect src_sdl_rect = static_cast<SDL_Rect>(src);
        SDL_Rect dst_sdl_rect = static_cast<SDL_Rect>(dst);        
        SDL_RenderCopy(m_renderer, tex.get_texture(), &src_sdl_rect, &dst_sdl_rect);
    }
    
    void graphics::draw_sprite(const sprite& spr, const vector2d& vec, int frame_number) const
    {
        throw std::runtime_error{"not implemented"};
    }
    
    void graphics::draw_sprite(const sprite& spr, const rect2d& rect, int frame_number) const
    {
        rect2d src_rect = spr.get_frame(frame_number);
        
        SDL_Rect src_sdl_rect = static_cast<SDL_Rect>(src_rect);
        SDL_Rect dst_sdl_rect = static_cast<SDL_Rect>(rect);
        
        SDL_RenderCopy(m_renderer, spr.get_texture(), &src_sdl_rect, &dst_sdl_rect);
    }
    
    void graphics::draw_ellipse(const color4f& color, const rect2d& rect)
    {
        vector2d size = rect.size() / 2;
        vector2d min = rect.center();
        
        aaellipseRGBA(m_renderer, min.x, min.y, size.x, size.y,
                    static_cast<uint8_t>(color.r),
                    static_cast<uint8_t>(color.g),
                    static_cast<uint8_t>(color.b),
                    static_cast<uint8_t>(color.a));
    }
    
    void graphics::draw_ellipse(const rect2d& rect)
    {
        draw_ellipse(m_color, rect);
    }
    
    void graphics::set_render_color(const color4f& color)
    {
        SDL_SetRenderDrawColor(m_renderer,
                               static_cast<uint8_t>(color.r),
                               static_cast<uint8_t>(color.g),
                               static_cast<uint8_t>(color.b),
                               static_cast<uint8_t>(color.a));
    }
    
    void graphics::draw_path(const color4f& color, const std::vector<node *> &nodes)
    {
        if (nodes.size() <= 1) {
            return;
        }
        
        rect2d small{0, 0, 4, 4};
        
        auto it = nodes.begin() + 1;
        for (; it != nodes.end(); ++it) {
            auto to = *it;
            auto from = *(it - 1);
            
            draw_line(color, from->get_position(), to->get_position());
            
            center(small, from->get_bounds());
            fill_rect(color, small);
        }
    }
    
    void graphics::draw_circle(const color4f& color, const vector2d& vec, double radius)
    {
        aacircleRGBA(m_renderer, vec.x, vec.y, radius,
                     static_cast<uint8_t>(color.r),
                     static_cast<uint8_t>(color.g),
                     static_cast<uint8_t>(color.b),
                     static_cast<uint8_t>(color.a));
    }
    
    void graphics::draw_circle(const vector2d& vec, double radius)
    {
        draw_circle(m_color, vec, radius);
    }
    
    void graphics::fill_circle(const color4f& color, const vector2d& vec, double radius)
    {
        filledCircleRGBA(m_renderer, vec.x, vec.y, radius,
                     static_cast<uint8_t>(color.r),
                     static_cast<uint8_t>(color.g),
                     static_cast<uint8_t>(color.b),
                     static_cast<uint8_t>(color.a));
    }
    
    void graphics::fill_circle(const vector2d& vec, double radius)
    {
        fill_circle(m_color, vec, radius);
    }
    
    void graphics::draw_string(const vector2d& vec, const std::string &str, const unsigned char options)
    {
        uint16_t w = FC_GetWidth(m_font, str.c_str());
        uint16_t h = FC_GetLineHeight(m_font);
        
        rect2d text_rect{0, 0, static_cast<double>(w), static_cast<double>(h)};
        align(vec, text_rect, options);
        
        FC_Draw(m_font, m_renderer, text_rect.min.x, text_rect.min.y, str.c_str());
    }
    
    void graphics::draw_string(const rect2d& rect, const std::string &str, const unsigned char options)
    {
        uint16_t w = FC_GetWidth(m_font, str.c_str());
        uint16_t h = FC_GetLineHeight(m_font);
        
        rect2d text_rect{0, 0, static_cast<double>(w), static_cast<double>(h)};
        align(rect, text_rect, options);
        
        FC_Draw(m_font, m_renderer, text_rect.min.x, text_rect.min.y, str.c_str());
    }
    
    window& graphics::get_window() const
    {
        return m_window;
    }
    
    SDL_Renderer* graphics::get_renderer()
    {
        return m_renderer;
    }
    
    const SDL_Renderer* graphics::get_renderer() const
    {
        return m_renderer;
    }
    
    color4f graphics::get_color()
    {
        return m_color;
    }
    
    const color4f& graphics::get_color() const
    {
        return m_color;
    }
    
    void graphics::set_color(const color4f& color)
    {
        set_render_color(color);
        m_color = color;
    }
    
    color4f graphics::get_clear_color()
    {
        return m_clear_color;
    }
    
    const color4f& graphics::get_clear_color() const
    {
        return m_clear_color;
    }
    
    void graphics::set_clear_color(const color4f& color)
    {
        m_clear_color = color;
    }
}
