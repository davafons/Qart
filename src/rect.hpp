#pragma once

#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "surface.hpp"


class Rect
{
    public:
        Rect(Surface * parent_surface, SDL_Rect rect);
        Rect(Surface * parent_surface = nullptr, int x = 0 , int y = 0, int w = 0, int h = 0);
        Rect & operator=(const Rect & rhs);

        int x() const { return rect_.x; }
        int y() const { return rect_.y; }
        int w() const { return rect_.w; }
        int h() const { return rect_.h; }

        Surface * getSurface() const { return parent_surface_; }
        SDL_Color averageColor() const { return average_color_; }
        double error() const { return error_; }

        void render(SDL_Renderer * renderer) const;

        operator SDL_Rect() { return rect_; }
        bool operator<(const Rect & rhs) const { return error_ < rhs.error_; }

        static bool & show_borderlines() { return borderlines_enabled_; }

    private:
        Surface * parent_surface_;

        SDL_Rect rect_;
        SDL_Color average_color_;
        double error_;

        static bool borderlines_enabled_;

        void calculateAverageColor();
        void calculateError();
};