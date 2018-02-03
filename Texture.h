#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:

	// Texture
	SDL_Texture * texture_;

	// Texture information
	SDL_PixelFormat fmt_;
	void * pixels_;
	int pitch_;

	// Texture dimensions
	int width_;
	int height_;

public:

	Texture(void);
	~Texture(void);

	// Getters
	int getWidth(void) const;
	int getHeight(void) const;

	bool load(const char * path, SDL_Window * window, SDL_Renderer * renderer);

	SDL_Color getAverageColor(SDL_Rect src);

	void render(SDL_Renderer * renderer, int x, int y, SDL_Rect * clip) const;

private:

	void free(void);

	Uint32 getpixel(int x, int y);
};

