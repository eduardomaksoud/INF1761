#include <SDL.h>

#include <iostream>
#include <cstdlib>

#include "Scene.h"
#include "Application.h"

#define WIDTH 550
#define HEIGHT 550

static bool running = true;
static Application* application = nullptr;

static void HandleEvents(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		application->OnKeyPressed(e.key.keysym.sym);
		break;

	case SDL_KEYUP:
		application->OnKeyReleased(e.key.keysym.sym);
		break;

	case SDL_QUIT:
		running = false;
		break;
	}
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error when trying to initialize SDL!\n";
        std::exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(
        "Raytracing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);

    if (window == NULL)
    {
        std::cerr << "Error when trying to create window!\n";
        std::exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cerr << "Error when trying to create renderer!\n";
        std::exit(1);
    }

    SDL_Event event;

	RenderingFrame renderingFrame;
	renderingFrame.setWidth(WIDTH);
	renderingFrame.setHeight(HEIGHT);
	renderingFrame.renderer = renderer;

	application = new Application(&renderingFrame);

	Uint64 thisTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = 0;
	float deltaTime = 0;

	application->OnStart();

    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
			HandleEvents(event);
        }
		
		lastTick = thisTick;
		thisTick = SDL_GetPerformanceCounter();

		deltaTime = (double)((thisTick - lastTick) / (double)SDL_GetPerformanceFrequency());

		application->OnUpdate(deltaTime);
		application->OnDraw();
    }

    return 0;
}
