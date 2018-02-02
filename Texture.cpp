#include <iostream>

#include "Texture.h"


Texture::Texture():
	texture_(nullptr),
	pixels_(nullptr),
	pitch_(0),
	width_(0),
	height_(0)
{
}


Texture::~Texture(void)
{
	free();
}


int Texture::getWidth(void) const
{
	return width_;
}


int Texture::getHeight(void) const
{
	return height_;
}


bool Texture::load(const char * path, SDL_Window * window, SDL_Renderer * renderer)
{
	SDL_Surface * tempSurface = IMG_Load(path);

	// Save pixel format
	fmt_ = *tempSurface->format;

	std::cout << SDL_GetPixelFormatName(fmt_.format) << std::endl;

	if (tempSurface == nullptr)
		throw IMG_GetError();

	SDL_Texture * nTexture = SDL_CreateTexture(renderer, fmt_.format, SDL_TEXTUREACCESS_STREAMING, tempSurface->w, tempSurface->h);

	if (nTexture == nullptr)
		throw SDL_GetError();

	SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);

	// Lock and copy pixels
	SDL_LockTexture(nTexture, nullptr, &pixels_, &pitch_);

	memcpy(pixels_, tempSurface->pixels, tempSurface->pitch * tempSurface->h);

	SDL_UnlockTexture(nTexture);

	pixels_ = nullptr;

	// Copy surface dimensions
	width_ = tempSurface->w;
	height_ = tempSurface->h;

	SDL_FreeSurface(tempSurface);

	texture_ = nTexture;

	return texture_ != nullptr;
}


SDL_Color Texture::getAverageColor(SDL_Rect src)
{
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;

	std::cout << "Format" << SDL_GetPixelFormatName(fmt_.format) << std::endl;

	// Lock Texture
	SDL_LockTexture(texture_, &src, &pixels_, &pitch_);

	for (int y = 0; y < src.h; ++y)
	{
		for (int x = 0; x < src.w; ++x)
		{
			Uint8 r; Uint8 g; Uint8 b; Uint8 a;

			SDL_GetRGBA(getpixel(x, y), &fmt_, &r, &g, &b, &a);

			if (a)
			{
				totalR += (int)r;
				totalG += (int)g;
				totalB += (int)b;
				//std::cout << (int)r << " " << (int)g << " " << (int)b << " " << (int)a << " " << std::endl;
			}
		}
	}

	// Unlock Texture
	SDL_UnlockTexture(texture_);

	SDL_Color average = { totalR / ((src.w * src.h)), totalG / ((src.w * src.h)), totalB / (src.w * src.h), 255 };

	std::cout << (int)average.r << " " << (int)average.g << " " << (int)average.b << " " << (int)average.a << " " << std::endl;

	return average;
}


void Texture::render(SDL_Renderer * renderer, int x, int y, SDL_Rect * clip)
{
	SDL_Rect renderQuad = { x, y, width_, height_ };

	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture_, clip, &renderQuad);
}



void Texture::free(void)
{
	SDL_DestroyTexture(texture_);
	SDL_FreeFormat(&fmt_);
}

Uint32 Texture::getpixel(int x, int y)
{
	Uint8 *p = (Uint8 *)pixels_ + y * pitch_ + x * fmt_.BytesPerPixel;

	switch (fmt_.BytesPerPixel)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;
	
	default:
		return 0;
	}
}
