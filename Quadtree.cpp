#include <cmath>

#include "Quadtree.h"

Quadtree::Quadtree(std::unique_ptr<SDL_Surface> & image, int level, const SDL_Rect & rect) :
	image_(image),
	rect_(rect),
	level_(level),
	av_color_(SDL_Color()),
	error_(0.0),
	leafs_(std::vector<Quadtree>())
{
	calculateColorAndError();
}


Quadtree::~Quadtree() {}


double Quadtree::getError(void) const { return error_; }


void Quadtree::clear(void) { leafs_.clear(); }


void Quadtree::split(SDL_Renderer * renderer, bool outline)
{
	// There is no need to check if the square is bigger than 1 (pixel), those will have 0.0 error when constructed

	int subwidth = (float)rect_.w / 2 + 0.5;
	int subheight = (float)rect_.h / 2 + 0.5;

	leafs_.emplace_back(image_, level_ + 1, SDL_Rect{ rect_.x, rect_.y, subwidth , subheight  });								// Top left
	leafs_.emplace_back(image_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y, subwidth, subheight });					// Top right
	leafs_.emplace_back(image_, level_ + 1, SDL_Rect{ rect_.x, rect_.y + rect_.h / 2, subwidth, subheight });					// Bot left
	leafs_.emplace_back(image_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y + rect_.h / 2, subwidth, subheight });		// Bot right

	for (auto & leaf : leafs_)
		leaf.render(renderer, outline);
}


Quadtree * Quadtree::findWorst(void)
{
	if (leafs_.empty())
		return this;

	double worst_error = 0;
	Quadtree * worst = nullptr;

	for (auto & leaf : leafs_)
	{
		Quadtree * temp = leaf.findWorst(); // Recursive call

		if (temp != nullptr)
		{
			double temp_error = temp->getError();

			if (temp_error > worst_error)
			{
				worst_error = temp_error;
				worst = temp;
			}
		}
	}
	return worst;
}


void Quadtree::render(SDL_Renderer * renderer, bool outline) const
{
	SDL_SetRenderDrawColor(renderer, av_color_.r, av_color_.g, av_color_.b, av_color_.a);
	SDL_RenderFillRect(renderer, &rect_);

	if (outline) // Renders black borders if true
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &rect_);
	}
}


void Quadtree::calculateColorAndError(void)
{
	int totalR = 0, totalG = 0, totalB = 0;

	SDL_LockSurface(image_.get()); // Lock surface for pixel manipulation

	// Calculate average color
	for (int y = rect_.y; y < rect_.y + rect_.h; ++y)
	{
		for (int x = rect_.x; x < rect_.x + rect_.w; ++x)
		{
			Uint8 r, g, b;

			SDL_GetRGB(getPixel32(x, y), image_->format, &r, &g, &b);

			totalR += r;
			totalG += g;
			totalB += b;
		}
	}

	av_color_ = { Uint8(totalR / (rect_.w * rect_.h)), Uint8(totalG / (rect_.w * rect_.h)), Uint8(totalB / (rect_.w * rect_.h)), 0xFF };

	// Calculate error (Difference between the average color and each pixel)
	for (int y = rect_.y; y < rect_.y + rect_.h; ++y)
	{
		for (int x = rect_.x; x < rect_.x + rect_.w; ++x)
		{
			Uint8 r, g, b;

			SDL_GetRGB(getPixel32(x, y), image_->format, &r, &g, &b);

			error_ += std::pow((int)r - (int)av_color_.r, 2);
			error_ += std::pow((int)g - (int)av_color_.g, 2);
			error_ += std::pow((int)b - (int)av_color_.b, 2);
		}
	}

	error_ /= rect_.w;

	SDL_UnlockSurface(image_.get());
}


Uint32 Quadtree::getPixel32(int x, int y) const
{
	Uint8 * p = (Uint8 *)image_->pixels + y * image_->pitch + x * 4;

	return *(Uint32 *)p;
}
