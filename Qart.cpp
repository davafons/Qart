#include "Qart.h"

Qart::Qart(void) :
	Engine(),
	image_(Texture()),
	qtree_(nullptr),
	squares_(0)
{
}


Qart::~Qart(void)
{
	delete qtree_;
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
			// Get image path
			char * path = e.drop.file;

			image_.load(path, window_);

			SDL_free(path);

			delete qtree_;
			qtree_ = new Quadtree(nullptr, image_, 0, SDL_Rect{ 0, 0, SCREEN_WIDTH_, SCREEN_HEIGHT_ });
			squares_ = 1;
		}

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				quit_ = true;

			if (e.key.keysym.sym == SDLK_s)
			{
				if(qtree_ != nullptr)
					qtree_->split();
			}
		}
	}
}


void Qart::update(void)
{
	if(qtree_ != nullptr)
		qtree_->split();
}


void Qart::render(void)
{
	SDL_RenderClear(renderer_);

	if (qtree_ != nullptr)
		qtree_->render(renderer_);

	SDL_RenderPresent(renderer_);
}


