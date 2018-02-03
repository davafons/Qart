#include <iostream>

#include "Texture.h"


Texture::Texture():
	surface_(nullptr)
{
}


Texture::~Texture(void)
{
	free();
}


int Texture::getWidth(void) const
{
	return surface_->w;
}


int Texture::getHeight(void) const
{
	return surface_->h;
}


bool Texture::load(const char * path, SDL_Window * window)
{
	free();

	// Load image
	SDL_Surface * tempSurface = IMG_Load(path);

	if (tempSurface == nullptr)
		throw IMG_GetError();

	// Converting to a 32bpp surface allows to scale size and save alpha channel in .png files
	SDL_Surface * p32bppSurface = SDL_CreateRGBSurface(tempSurface->flags, tempSurface->w, tempSurface->h, 32, tempSurface->format->Rmask, tempSurface->format->Gmask, tempSurface->format->Bmask, tempSurface->format->Amask);

	if (SDL_BlitSurface(tempSurface, nullptr, p32bppSurface, nullptr) < 0)
		throw SDL_GetError();

	// Scale image to screen dimensions
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	surface_ = SDL_CreateRGBSurface(p32bppSurface->flags, w, h, p32bppSurface->format->BitsPerPixel, p32bppSurface->format->Rmask, p32bppSurface->format->Gmask, p32bppSurface->format->Bmask, p32bppSurface->format->Amask);

	if (SDL_BlitScaled(p32bppSurface, nullptr, surface_, nullptr) < 0)
		throw SDL_GetError();
	
	// Free alloc memory
	SDL_FreeSurface(tempSurface);
	SDL_FreeSurface(p32bppSurface);

	return surface_ != nullptr;
}


SDL_Color Texture::getAverageColor(SDL_Rect src)
{
	///std::cout << src.x << " " << src.y << " " << src.w << " " << src.h << std::endl;

	int totalR = 0, totalG = 0, totalB = 0;

	// Lock Surface for pixel manipulation
	SDL_LockSurface(surface_);

	for (int y = src.y; y < src.y + src.h; ++y)
	{
		for (int x = src.x; x < src.x + src.w; ++x) 
		{
			Uint8 r, g, b;

			SDL_GetRGB(getpixel32(x, y), surface_->format, &r, &g, &b);
			
			totalR += r;
			totalG += g;
			totalB += b;
		}
	}

	// Unlock Surface
	SDL_UnlockSurface(surface_);

	// Average color = total color value / area
	SDL_Color average_color = { totalR / (src.w * src.h), totalG / (src.w * src.h), totalB / (src.w * src.h), 255 };
	///std::cout << (int)average_color.r << " " << (int)average_color.g << " " << (int)average_color.b << " " << (int)average_color.a << " " << std::endl;

	return average_color;
}


void Texture::free(void)
{
	SDL_FreeSurface(surface_);
}


Uint32 Texture::getpixel32(int x, int y) const
{
	Uint8 *p = (Uint8 *)surface_->pixels + y * surface_->pitch + x * surface_->format->BytesPerPixel; // * 4 <- Image already converted to bpp32 (Bpp4)

	return *(Uint32 *)p;
}
