#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:
	SDL_Surface * surface_;

public:
	Texture(void);
	~Texture(void);

	int getWidth(void) const;
	int getHeight(void) const;

	bool load(const char * path, SDL_Window * window);

	SDL_Color getAverageColor(SDL_Rect src);

private:
	void free(void);

	Uint32 getpixel32(int x, int y) const;
};

