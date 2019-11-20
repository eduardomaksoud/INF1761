#ifndef RENDERING_FRAME_H
#define RENDERING_FRAME_H

#include <vector>

#include <SDL.h>

class RenderingFrame
{
public:
	inline int getWidth() const { return width; }
	inline void setWidth(int w) { width = w; }
	inline int getHeight() const { return height; }
	inline void setHeight(int h) { height = h; }

	SDL_Renderer* renderer = nullptr;

	inline void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
	}

	inline void setColor(const SDL_Color& color)
	{
		setColor(color.r, color.g, color.b, color.a);
	}

	inline void drawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(renderer, x, y);
	}

	inline void drawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(renderer, x, y);
	}

private:
	int width;
	int height;
};

#endif // RENDERING_FRAME_H