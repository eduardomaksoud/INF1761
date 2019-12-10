#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Vector3.h"
#include <SDL.h>

struct PointLight 
{
	Vector3 position;

    float intensity;
	SDL_Color color;
};


#endif // POINTLIGHT_H