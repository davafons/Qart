#pragma once

#include "Engine.h"
#include "Texture.h"
#include "Quadtree.h"

class Qart : public Engine
{
private:

	Texture image_;
	Quadtree * qtree_;

public:
	Qart(void);
	~Qart();

	void execute(void);

	void input(void);

	void update(void);

	void render(void);
};

