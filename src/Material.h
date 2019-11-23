#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL.h>

class Material
{
public:
	const SDL_Color& getColor() const { return color; }
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

private:
	SDL_Color color;
};

#endif // MATERIAL_H