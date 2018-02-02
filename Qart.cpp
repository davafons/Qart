#include "Qart.h"

Qart::Qart(void) :
	Engine(),
	quit_(false)
{
}


Qart::~Qart(void)
{
}


void Qart::execute(void)
{
	while (!quit_)
	{
		input();
		update();
		render();
	}
}


void Qart::input(void)
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT ||
			e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit_ = true;
		}

		if (e.type == SDL_DROPFILE)
		{
			char * path = e.drop.file;

			image_.load(path, window_, renderer_);

			SDL_free(path);

			average_color_ = image_.getAverageColor(SDL_Rect({ 0, 0, image_.getWidth(), image_.getHeight() }));
		}
	}
}


void Qart::update(void)
{

}


void Qart::render(void)
{
	SDL_SetRenderDrawColor(renderer_, average_color_.r, average_color_.g, average_color_.b, average_color_.a);

	SDL_RenderClear(renderer_);

	image_.render(renderer_, 0, 0, nullptr);

	SDL_RenderPresent(renderer_);
}


