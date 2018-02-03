#include "Qart.h"

Qart::Qart(void) :
	Engine(),
	image_(Texture()),
	qtree_(nullptr)
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
		if (e.type == SDL_QUIT)
			quit_ = true;

		if (e.type == SDL_DROPFILE)
		{
			char * path = e.drop.file;

			image_.load(path, window_, renderer_);

			SDL_free(path);

			qtree_ = new Quadtree(image_, 0, SDL_Rect{ 0, 0, image_.getWidth(), image_.getHeight() });
			
			qtree_->getAverageColor();
		}

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				quit_ = true;

			if (e.key.keysym.sym == SDLK_s)
				qtree_->split();
		}
	}
}


void Qart::update(void)
{

}


void Qart::render(void)
{
	SDL_RenderClear(renderer_);

	image_.render(renderer_, 0, 0, nullptr);

	if (qtree_ != nullptr)
	{
		qtree_->render(renderer_);
	}


	SDL_RenderPresent(renderer_);
}


