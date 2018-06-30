#include "screen.hpp"

Screen::Screen(const char * title, int width, int height) : 
    window_(nullptr),
    renderer_(nullptr),
    closed_(true)
{
    if(SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            throw SDL_GetError();
    }

    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if(window_ == nullptr)
        throw SDL_GetError();

    renderer_ = SDL_CreateRenderer(window_, 0, SDL_RENDERER_ACCELERATED);
    if(renderer_ == nullptr)
        throw SDL_GetError();

    SDL_SetRenderDrawColor(renderer_, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);

    closed_ = false;
}


Screen::~Screen()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}


void Screen::setWindowTitle(const std::string & title) const
{
    SDL_SetWindowTitle(window_, title.c_str());
}


void Screen::setWindowSize(int width, int height) const
{
    SDL_SetWindowSize(window_, width, height);
}


void Screen::clear() const
{
    SDL_SetRenderDrawColor(renderer_, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderClear(renderer_);
}

int Screen::width() const
{
    int width;
    SDL_GetWindowSize(window_, &width, nullptr);
    return width;
}


int Screen::height() const
{
    int height;
    SDL_GetWindowSize(window_, nullptr, &height);
    return height;
}