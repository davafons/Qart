#pragma once

#include "Engine.h"
#include "Texture.h"

class Qart : public Engine
{
private:

	bool quit_;

	Texture image_;

	SDL_Color average_color_;

public:
	Qart(void);
	~Qart();

	void execute(void);

	void input(void);

	void update(void);

	void render(void);
};

