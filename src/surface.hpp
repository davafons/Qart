#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Surface
{
    public:
        Surface(const char * path = nullptr, int width = 0, int height = 0);
        ~Surface();

        int width() const { return (surface_) ? surface_->w : 0; }
        int height() const { return (surface_) ? surface_->h : 0; }

        void load(const char * path, int width = 0, int height = 0);
        bool isLoaded() const { return surface_ != nullptr; }

        void lock();
        void unlock();

        void getPixelColor(int x, int y, Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a) const;

    private:
        SDL_Surface * surface_;

        static bool IMG_Initialized;
        static int MAX_WIDTH;
        static int MAX_HEIGHT;

        void adaptToMaxSize(int & width, int & height) const;

        Uint32 getPixel32(int x, int y) const;
};