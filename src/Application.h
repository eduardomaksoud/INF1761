#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>

#include "Scene.h"
#include "RenderingFrame.h"

class Application
{
public:
	Application(RenderingFrame* rf);

	void OnStart();
	void OnUpdate(float dt);
	void OnDraw();
	void OnKeyPressed(SDL_Keycode kc);
	void OnKeyReleased(SDL_Keycode kc);
	void OnMouseMove(float dx, float dy);

private:
	Scene* scene = nullptr;
	RenderingFrame* frame;
};

#endif // APPLICATION_H