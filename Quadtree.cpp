#include <algorithm>
#include <cmath>

#include "Quadtree.h"

Quadtree::Quadtree(Quadtree * parent, Texture & texture, int level, const SDL_Rect& rect) :
	texture_(texture),
	level_(level),
	rect_(rect),
	parent_(parent),
	nodes_(std::vector<std::unique_ptr<Quadtree> >(4))
{
	average_color_ = texture_.getAverageColor(rect_);
	calcError();
	std::cout << "Node x: " << rect.x << " y: " << rect.y << " Error: " << error_ << std::endl;
}


Quadtree::~Quadtree()
{
	nodes_.clear();
}

SDL_Color Quadtree::getAverageColor(void) const
{
	return average_color_;
}


void Quadtree::split(void)
{
	if (rect_.w > 1) // Can't subdivide a node that is 1 pixel width
	{
		///std::cout << rect_.h / 2 << "Round" << (float)rect_.h / 2 + 0.5f << std::endl;
		///std::cout << subwidth << " " << subheight << std::endl;

		if (nodes_[0] != nullptr)
		{
			int max = nodes_[0]->getError();
			int ix = 0;
			for (int i = 0; i < 4; ++i)
			{
				if (nodes_[i]->getError() > max)
				{
					max = nodes_[i]->getError();
					ix = i;
				}
			}
			nodes_[ix]->split();

		}
		else 
		{
			int subwidth = (float)rect_.w / 2 + 0.5;
			int subheight = (float)rect_.h / 2 + 0.5;

			nodes_[0] = std::make_unique<Quadtree>(this, texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y, subwidth, subheight });									// Top left
			nodes_[1] = std::make_unique<Quadtree>(this, texture_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y, subwidth, subheight });					// Top right
			nodes_[2] = std::make_unique<Quadtree>(this, texture_, level_ + 1, SDL_Rect{ rect_.x, rect_.y + rect_.h / 2, subwidth, subheight });					// Bot left
			nodes_[3] = std::make_unique<Quadtree>(this, texture_, level_ + 1, SDL_Rect{ rect_.x + rect_.w / 2, rect_.y + rect_.h / 2, subwidth, subheight });		// Bot right
		
			error_ = 0;
		}
	}
}


void Quadtree::calcError(void)
{
	if (parent_ != nullptr)
	{
		int re = abs(parent_->getAverageColor().r - average_color_.r);
		int ge = abs(parent_->getAverageColor().g - average_color_.g);
		int be = abs(parent_->getAverageColor().b - average_color_.b);

		error_ = re + ge + be;
	}
	else
		error_ = 100;
}

int Quadtree::getError(void) const
{
	return error_;
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

bool Quadtree::operator<(const Quadtree & quad) const
{
	return error_ < quad.error_;
}

