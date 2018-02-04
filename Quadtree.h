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
	int error_;

	Quadtree * parent_;
	std::vector<std::unique_ptr<Quadtree> > nodes_;

public:
	Quadtree(Quadtree * parent, Texture & texture, int level, const SDL_Rect& rect);
	~Quadtree();

	SDL_Color getAverageColor(void) const;

	void split(void);

	void calcError(void);

	int getError(void) const;

	void render(SDL_Renderer * renderer) const;

	bool operator<(const Quadtree & quad) const;
};

