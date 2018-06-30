#pragma once

#include <string>

#include <SDL2/SDL.h>

class Screen
{
    public:
        Screen(const char * title, int width, int height);
        ~Screen();

        bool isClosed() const { return closed_; }
        void close() { closed_ = true; }

        SDL_Renderer * renderer() const { return renderer_; }

        void setWindowSize(int width, int height) const;
        void setWindowTitle(const std::string & title) const;
        void clear() const;

        int width() const;
        int height() const;

    private:
        SDL_Window * window_;
        SDL_Renderer * renderer_;

        bool closed_;
};