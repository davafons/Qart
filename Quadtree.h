#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <vector>
#include <memory>

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

class Quadtree
{
private:

	std::unique_ptr<SDL_Surface> & image_;
	SDL_Rect rect_;

	int level_;

	SDL_Color av_color_;
	double error_;

	std::vector<Quadtree> leafs_;

public:

	Quadtree(std::unique_ptr<SDL_Surface> & image, int level, const SDL_Rect & rect);

	~Quadtree(void);

	double getError(void) const;

	void clear(void);

	// Create 4 new leafs
	void split(SDL_Renderer * renderer, bool outline);

	// Loop through every leaf recursively finding the node with the worst error. Linear to the number of empty leafs in the whole tree
	Quadtree * findWorst(void);

	void render(SDL_Renderer * renderer, bool outline) const;

private:

	void calculateColorAndError(void);

	Uint32 getPixel32(int x, int y) const;
};

#endif /* QUADTREE_H_ */
