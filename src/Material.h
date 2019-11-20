#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL.h>

class Material
{
public:
	const SDL_Color& getColor() const { return color; }

private:
	SDL_Color color;
};

#endif // MATERIAL_H