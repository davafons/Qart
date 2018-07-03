#pragma once

#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "surface.hpp"


/* This class represents a sub-rectangle in a Surface. Both average color
   and error are calculated when calling the constructor, so aditional calls
   to these functions aren't necessary (They are private indeed) */

class Rect
{
    public:
        Rect(Surface & parent_surface, SDL_Rect rect);
        Rect(Surface & parent_surface, int x = 0 , int y = 0, int w = 0, int h = 0);
        Rect & operator=(const Rect & rhs);

        int x() const { return rect_.x; }
        int y() const { return rect_.y; }
        int w() const { return rect_.w; }
        int h() const { return rect_.h; }

        SDL_Color averageColor() const { return average_color_; }
        double error() const { return error_; }

        void render(SDL_Renderer * renderer) const;

        bool operator<(const Rect & rhs) const { return error_ < rhs.error_; }

        static bool & show_borders() { return borders_enabled_; }

    private:
        Surface & parent_surface_;

        SDL_Rect rect_;
        SDL_Color average_color_;
        double error_;

        static bool borders_enabled_;

        void calculateAverageColor();
        void calculateError();
};