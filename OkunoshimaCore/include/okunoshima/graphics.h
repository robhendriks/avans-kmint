#ifndef graphics_h
#define graphics_h

#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "rect2d.h"
#include "color4f.h"
#include "texture.h"
#include "sprite.h"
#include "window.h"
#include "node.h"
#include "SDL_FontCache.h"
#include "align.h"

namespace okunoshima
{
    class graphics
    {
        window& m_window;
        SDL_Renderer* m_renderer;
        color4f m_color, m_clear_color;
        FC_Font* m_font;
        
        void init();
        void set_render_color(const color4f& color);
    public:
        graphics(window& w);
        ~graphics();
        
        void clear();
        void display();
        void draw_rect(const rect2d& rect) const;
        void draw_rect(const color4f& color, const rect2d& rect);
        void fill_rect(const rect2d& rect) const;
        void fill_rect(const color4f& color, const rect2d& rect);
        void draw_line(const vector2d& p1, const vector2d& p2) const;
        void draw_line(const color4f& color, const vector2d& p1, const vector2d& p2);
        void draw_texture(const texture& tex, const vector2d& vec) const;
        void draw_texture(const texture& tex, const rect2d& dst) const;
        void draw_texture(const texture& tex, const rect2d& src, const rect2d& dst) const;
        void draw_sprite(const sprite& spr, const vector2d& vec, int frame_number) const;
        void draw_sprite(const sprite& spr, const rect2d& rect, int frame_number) const;
        void draw_ellipse(const rect2d& rect);
        void draw_ellipse(const color4f& color, const rect2d& rect);
        void draw_circle(const color4f& color, const vector2d& vec, double radius);
        void draw_circle(const vector2d& vec, double radius);
        void fill_circle(const color4f& color, const vector2d& vec, double radius);
        void fill_circle(const vector2d& vec, double radius);
        void draw_path(const color4f& color, const std::vector<node*>& nodes);
        void draw_string(const vector2d& vec, const std::string& str, const unsigned char options = align_default);
        void draw_string(const rect2d& rect, const std::string &str, const unsigned char options = align_default);
        
        window& get_window() const;
        SDL_Renderer* get_renderer();
        const SDL_Renderer* get_renderer() const;
        color4f get_color();
        const color4f& get_color() const;
        void set_color(const color4f& color);
        color4f get_clear_color();
        const color4f& get_clear_color() const;
        void set_clear_color(const color4f& color);
    };
}

#endif
