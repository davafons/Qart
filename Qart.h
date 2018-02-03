#pragma once

#include <set>

#include "Engine.h"
#include "Texture.h"
#include "Quadtree.h"

class Qart : public Engine
{
private:
	Texture image_;
	Quadtree * qtree_;
	
	std::set<std::shared_ptr<Quadtree> > squares_;

public:
	Qart(void);
	~Qart();

	void execute(void);

	void input(void);

	void update(void);

	void render(void);
};

