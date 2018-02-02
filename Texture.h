#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:

	SDL_Texture * texture_;

	SDL_PixelFormat fmt_;

	void * pixels_;
	int pitch_;

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

	void render(SDL_Renderer * renderer, int x, int y, SDL_Rect * clip);

private:

	void free(void);

	Uint32 getpixel(int x, int y);
};

