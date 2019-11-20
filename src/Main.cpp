#include <SDL.h>

#include <iostream>
#include <cstdlib>

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
        1280, 720,
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

    bool running = true;
    SDL_Event event;

    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    std::cout << "vlw flw";
                    running = false;
                    break;
            }
        }
    }

    return 0;
}
