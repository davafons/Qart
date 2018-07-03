#include <iostream>

#include "surface.hpp"

bool Surface::IMG_Initialized_ = false;
const int Surface::MAX_WIDTH_ = 1280;
const int Surface::MAX_HEIGHT_ = 720;


Surface::Surface(const char * path, int width, int height)
{
    if(!IMG_Initialized_)
    {
        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
            throw IMG_GetError();
        
        IMG_Initialized_ = true;
    }

    if(path)
        load(path, width, height);
}


Surface::~Surface()
{
    SDL_FreeSurface(surface_);
}


void Surface::load(const char * path, int width, int height)
{
    try
    {
        if(path == nullptr)
            throw "Invalid path.";

        SDL_Surface * loaded_surface = IMG_Load(path);
        if(loaded_surface == nullptr)
            throw IMG_GetError();

        if(width == 0) width = loaded_surface->w;
        if(height == 0) height = loaded_surface->h;
        adaptToMaxSize(width, height);

        // The process of scaling a surface requires to create a new one with the desired properties
        SDL_Surface * scaled_surface = SDL_CreateRGBSurface(loaded_surface->flags, width, height, 32, loaded_surface->format->Rmask, loaded_surface->format->Gmask, loaded_surface->format->Bmask, loaded_surface->format->Amask);
        if(scaled_surface == nullptr)
            throw SDL_GetError();

        if(SDL_BlitScaled(loaded_surface, nullptr, scaled_surface, nullptr) < 0)
            throw SDL_GetError();

        SDL_FreeSurface(loaded_surface);

        surface_ = scaled_surface;

        std::cout << path << " loaded." << std::endl;
        std::cout << "Format: " << SDL_GetPixelFormatName(surface_->format->format) << std::endl;
        std::cout << surface_->w << "x" << surface_->h << " - npp " << (int)surface_->format->BitsPerPixel << std::endl;
    }
    catch(const char * msg)
    {
        std::cerr << "Error - Surface::load: " << msg << std::endl;
    }
}


void Surface::lock()
{
    if(SDL_LockSurface(surface_) < 0)
        throw SDL_GetError();
}


void Surface::unlock()
{
    SDL_UnlockSurface(surface_);
}


void Surface::getPixelColor(int x, int y, Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a) const
{
    if(surface_ == nullptr)
        std::cerr << "Error - Surface::getPixelColor: surface must be locked first." << std::endl;
    else
        SDL_GetRGBA(getPixel32(x, y), surface_->format, &r, &g, &b, &a);
}


void Surface::adaptToMaxSize(int & width, int & height) const
{
    float aspect_ratio = (float)width / height;

    if(width > MAX_WIDTH_)
    {
        width = MAX_WIDTH_;
        height = MAX_WIDTH_ / aspect_ratio + 0.5f;
    }
    else if(height > MAX_HEIGHT_)
    {
        width = MAX_HEIGHT_ * aspect_ratio + 0.5f;
        height = MAX_HEIGHT_;
    }
}


Uint32 Surface::getPixel32(int x, int y) const
{
    Uint8 * p = (Uint8*)surface_->pixels + y * surface_->pitch + x * surface_->format->BytesPerPixel;

    switch(surface_->format->BytesPerPixel)
    {
        case 1:
            return *p;
            break;
        case 2:
            return *(Uint16*)p;
            break;
        case 3: 
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;
        
        case 4:
            return *(Uint32*)p;

        default:
            return 0; // Should never happen
    }
}
