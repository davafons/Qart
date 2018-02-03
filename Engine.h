#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Engine
{
protected:

	// Attributes

	SDL_Window * window_;
	SDL_Renderer * renderer_;

	const int SCREEN_WIDTH_;
	const int SCREEN_HEIGHT_;

	bool quit_;


	// Functions

	Engine(void);
	~Engine(void);


	virtual void execute(void) = 0;

	virtual void input(void) = 0;

	virtual void update(void) = 0;

	virtual void render(void) = 0;
};

