#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <SDL.h>

#include "Texture.h"


class Quadtree
{
private:
	Texture & texture_; // Can't be null
	SDL_Color average_color_;

	SDL_Rect rect_; // Dimensions of the node

	int level_; // Current level
	float error_;

	std::vector<std::unique_ptr<Quadtree> > nodes_;

public:
	Quadtree(Texture& texture, int level, const SDL_Rect& rect);
	~Quadtree();

	void split(void);

	void render(SDL_Renderer * renderer) const;
};

