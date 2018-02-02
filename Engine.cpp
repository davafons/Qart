#include "Engine.h"

Engine::Engine(void):
	window_(nullptr),
	renderer_(nullptr),
	SCREEN_WIDTH_(800),
	SCREEN_HEIGHT_(600)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw SDL_GetError();

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw IMG_GetError();

	window_ = SDL_CreateWindow("Quadtree image art", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH_, SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);

	if (window_ == nullptr)
		throw SDL_GetError();

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (renderer_ == nullptr)
		throw SDL_GetError();

	SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);

	SDL_BlendMode(SDL_BLENDMODE_BLEND);
}


Engine::~Engine()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);

	IMG_Quit();
	SDL_Quit();
}
