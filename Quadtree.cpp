#include "Quadtree.h"

Quadtree::Quadtree(Texture& texture, int level, const SDL_Rect& rect) :
	texture_(texture),
	level_(level),
	rect_(rect),
	nodes_(std::vector<std::unique_ptr<Quadtree> >(4))
{
	average_color_ = texture_.getAverageColor(rect_);
}


Quadtree::~Quadtree()
{
	nodes_.clear();
}


void Quadtree::split(void)
{

	if (rect_.w > 1) // Can't subdivide a node that is 1 pixel width
	{
		///std::cout << rect_.h / 2 << "Round" << (float)rect_.h / 2 + 0.5f << std::endl;
		///std::cout << subwidth << " " << subheight << std::endl;

		if (nodes_[0] == nullptr)
		{
			int subwidth = (float)rect_.w / 2 + 0.5;
			int subheight = (float)rect_.h / 2 + 0.5;

			nodes_[0] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y, subwidth, subheight });								// Top left
			nodes_[1] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y, subwidth, subheight });					// Top right
			nodes_[2] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y + rect_.h / 2, subwidth, subheight });					// Bot left
			nodes_[3] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y + rect_.h / 2, subwidth, subheight });	// Bot right
		}
		else
		{
			for (auto & node : nodes_)
				node->split();
		}
	}
}


void Quadtree::render(SDL_Renderer * renderer) const
{
	if (nodes_[0] == nullptr)
	{
		SDL_SetRenderDrawColor(renderer, average_color_.r, average_color_.g, average_color_.b, average_color_.a);
		SDL_RenderFillRect(renderer, &rect_);
	}
	else
	{
		for (auto & node : nodes_)
			node->render(renderer);
	}
}