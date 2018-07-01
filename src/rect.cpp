#include "rect.hpp"

bool Rect::borderlines_enabled_ = false;

Rect::Rect(Surface * parent_surface, SDL_Rect rect) :
    parent_surface_(parent_surface),
    rect_(rect)
{
    if(parent_surface_)
    {
        calculateAverageColor();
        calculateError();
    }
}


Rect::Rect(Surface * parent_surface, int x, int y, int w, int h) :
    Rect(parent_surface, SDL_Rect{x, y, w, h})
{
}


Rect & Rect::operator=(const Rect & rhs)
{
    parent_surface_ = rhs.parent_surface_;
    rect_ = rhs.rect_;
    average_color_ = rhs.average_color_;
    error_ = rhs.error_;

    return * this;
}


void Rect::calculateAverageColor()
{
    int totalR, totalG, totalB, totalA;
    totalR = totalG = totalB = totalA = 0;

    parent_surface_->lock();

    for(int j = y(); j < h() + y(); ++j)
    {
        for(int i = x(); i < w() + x(); ++i)
        {
            Uint8 r, g, b, a;
            parent_surface_->getPixelColor(i, j, r, g, b, a);

            totalR += r;
            totalG += g;
            totalB += b;
            totalA += a;
        }
    }

    parent_surface_->unlock();

    int area = w() * h();

    SDL_Color average_color { Uint8(totalR / area), Uint8(totalG / area), Uint8(totalB / area), Uint8(totalA / area)};

    average_color_ = average_color;
}


void Rect::render(SDL_Renderer * renderer) const
{
    SDL_SetRenderDrawColor(renderer, average_color_.r, average_color_.g, average_color_.b, average_color_.a);
    SDL_RenderFillRect(renderer, &rect_);

    if(borderlines_enabled_)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &rect_);
    }

    SDL_RenderPresent(renderer);
}


void Rect::calculateError()
{
    double error = 0.0f;

    parent_surface_->lock();

    for(int j = y(); j < h() + y(); ++j)
    {
        for(int i = x(); i < w() + x(); ++i)
        {
            Uint8 r, g, b, a;
            parent_surface_->getPixelColor(i, j, r, g, b, a);

            error += std::pow((int)r - (int)average_color_.r, 2);        
            error += std::pow((int)g - (int)average_color_.g, 2);        
            error += std::pow((int)b - (int)average_color_.b, 2);        
            error += std::pow((int)a - (int)average_color_.a, 2);        
        }
    }

    parent_surface_->unlock();

    error /= w();

    error_ = error;
}