#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL.h>

class Material
{
public:
	const SDL_Color& getDiffuseColor() const { return diffuseColor; }
	const SDL_Color& getSpecularColor() const { return specularColor; }

	void setDiffuseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
	{
		diffuseColor.r = r;
		diffuseColor.g = g;
		diffuseColor.b = b;
		diffuseColor.a = a;
	}

private:
	SDL_Color diffuseColor;
	SDL_Color specularColor;
};

#endif // MATERIAL_H