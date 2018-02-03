#include "Quadtree.h"

Quadtree::Quadtree(Texture& texture, int level, const SDL_Rect& rect) :
	texture_(texture),
	level_(level),
	average_color_(SDL_Color()),
	rect_(rect),
	nodes_(std::vector<std::unique_ptr<Quadtree> >(4))
{
}


Quadtree::~Quadtree()
{
	nodes_.clear();
}


void Quadtree::split(void)
{
	if (nodes_[0] == nullptr)
	{
		nodes_[0] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y, rect_.w / 2, rect_.h / 2 });
		nodes_[1] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x + (rect_.w / 2), rect_.y, rect_.w / 2, rect_.h });
		nodes_[2] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y + (rect_.h / 2), rect_.w / 2, rect_.h / 2 });
		nodes_[3] = std::make_unique<Quadtree>(texture_, level_ + 1, SDL_Rect{ rect_.x + (rect_.w / 2), rect_.y, rect_.w / 2, rect_.h / 2 });

		for (auto & node : nodes_)
		{
			node->getAverageColor();
		}
	}
	else
	{
		for (auto & node : nodes_)
		{
			node->split();
		}
	}
}

void Quadtree::getAverageColor(void)
{
	average_color_ = texture_.getAverageColor(rect_);
}


void Quadtree::render(SDL_Renderer * renderer) const
{
	SDL_SetRenderDrawColor(renderer, average_color_.r, average_color_.g, average_color_.b, average_color_.a);
	SDL_RenderFillRect(renderer, &rect_);

	//std::cout << rect_.x << " " << rect_.y << " " << rect_.w << " " << rect_.h << std::endl;


	for (auto & node : nodes_)
	{
		if (node != nullptr)
		{
			node->render(renderer);
		}
	}
}