#include <iostream>
#include <memory>
#include <sstream>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Quadtree.h"

std::unique_ptr<SDL_Surface> loadSurface(const char * path, const int width, const int height);

int main(int argc, char * argv[])
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	SDL_Window * window;
	SDL_Renderer * renderer;

	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw SDL_GetError();

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
			throw IMG_GetError();

		if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
			throw SDL_GetError();

		SDL_SetWindowTitle(window, "Qart - Drop an image on the window");

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	}
	catch (const char * msg)
	{
		std::cout << "Error: " << msg << std::endl;
		return 1;
	}


	bool quit = false;

	bool stop = true;
	bool outline = true;
	int iterations = 0;
	int squares = 1;

	std::unique_ptr<Quadtree> qtree(nullptr); // Parent node
	std::unique_ptr<SDL_Surface> image(nullptr);

	while (!quit)
	{
		// Input
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN && qtree != nullptr)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_s:
					stop = (stop) ? false : true;
					break;

				case SDLK_d:
					outline = (outline) ? false : true;
				case SDLK_r:
					qtree->clear();
					stop = false;
					iterations = 0;
					squares = 1;
					break;
				}
			}

			else if (e.type == SDL_DROPFILE)
			{
				char * path = e.drop.file;

				image = loadSurface(path, SCREEN_WIDTH, SCREEN_HEIGHT);

				if (image != nullptr)
				{
					qtree = std::make_unique<Quadtree>(image, 0, SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
					stop = false;
					iterations = 0;
					squares = 1;
				}

				SDL_free(path);
			}

			else if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}

		// Update
		if (!stop)
		{
			Quadtree * worst = qtree->findWorst();

			if (worst != nullptr)
			{
				worst->split(renderer, outline);

				squares += 3;
				std::stringstream title;
				title << "Qart - " << ++iterations << " iterations, " << squares << " squares created. Keyboard shortcuts: S: Start/Stop. R: Reset. D: Show outline";
				SDL_SetWindowTitle(window, title.str().c_str());
			}
			else
			{
				std::cout << "Finished in " << iterations << " iterations. " << squares << " squares created. Keyboard shortcuts: S: Start/Stop. R: Reset. D: Show outline" << std::endl;
				stop = true;
			}
		}

		SDL_RenderPresent(renderer); // There is no reason to clear the whole render in every frame, we just update with the new squares
	}


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(image.get());

	IMG_Quit();
	SDL_Quit();

	return 0;
}


std::unique_ptr<SDL_Surface> loadSurface(const char * path, const int width, const int height)
{
	try
	{
		// Load image
		SDL_Surface * loaded_surface = IMG_Load(path);
		if (loaded_surface == nullptr)
			throw IMG_GetError();

		// Transforming the loaded surface to a 32bpp surface allows to resize it
		SDL_Surface * surf_32bpp = SDL_CreateRGBSurface(loaded_surface->flags, loaded_surface->w, loaded_surface->h, 32, loaded_surface->format->Rmask, loaded_surface->format->Gmask, loaded_surface->format->Bmask, loaded_surface->format->Amask);
		if (surf_32bpp == nullptr)
			throw SDL_GetError();

		if (SDL_BlitSurface(loaded_surface, nullptr, surf_32bpp, nullptr) < 0)
			throw SDL_GetError();

		// Resize surface
		SDL_Surface * scaled_surface = SDL_CreateRGBSurface(surf_32bpp->flags, width, height, surf_32bpp->format->BitsPerPixel, surf_32bpp->format->Rmask, surf_32bpp->format->Gmask, surf_32bpp->format->Bmask, surf_32bpp->format->Amask);
		if (scaled_surface == nullptr)
			throw SDL_GetError();

		if (SDL_BlitScaled(surf_32bpp, nullptr, scaled_surface, nullptr) < 0)
			throw SDL_GetError();

		SDL_FreeSurface(loaded_surface);
		SDL_FreeSurface(surf_32bpp);

		return std::unique_ptr<SDL_Surface>(scaled_surface);
	}
	catch (const char * msg)
	{
		std::cout << "Error: " << msg << std::endl;
		return nullptr;
	}
}
