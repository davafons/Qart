#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Engine
{
protected:

	SDL_Window * window_;
	SDL_Renderer * renderer_;

	const int SCREEN_WIDTH_;
	const int SCREEN_HEIGHT_;

	Engine(void);
	~Engine(void);


	virtual void execute() = 0;

	virtual void input() = 0;

	virtual void update() = 0;

	virtual void render() = 0;
};

