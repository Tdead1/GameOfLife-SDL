#include "Graphics.h"

#include <iostream>
#include <vector>

#define SDL_MAIN_HANDLED
#include "Extern/SDL/SDL.h"

void Graphics::Init()
{
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	const int width = 640;
	const int height = 480;
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		" ",								// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		width,                              // width, in pixels
		height,                             // height, in pixels
		SDL_WINDOW_OPENGL					// flags - see below
	);


	// Check that the window was successfully created
	if (window == nullptr) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	/* Select the color for drawing. It is set to red here. */
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	/* Clear the entire screen to our selected color. */
	SDL_RenderClear(renderer);
	/* Up until now everything was drawn behind the scenes.
	   This will show the new, red contents of the window. */
	SDL_RenderPresent(renderer);
}

KEY Graphics::GetInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return KEY::ESC;
			if (event.key.keysym.sym == SDLK_SPACE)
				return KEY::SPACE;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			return KEY::MOUSELEFT;
		}
	}
	return KEY::NONE;
}

std::pair<int, int> Graphics::GetMousePosition()
{
	std::pair windowOffset{ 0,0 };
	std::pair position{ 0,0 };

	SDL_GetWindowPosition(window, &windowOffset.first, &windowOffset.second);
	SDL_GetGlobalMouseState(&position.first, &position.second);

	position.first -= windowOffset.first;
	position.second -= windowOffset.second;

	return position;
}

void Graphics::DrawRectangle(const int x, const int y, const int sizex, const int sizey)
{
	SDL_Rect rect;
	rect.h = sizey;
	rect.w = sizex;
	rect.x = x;
	rect.y = y;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	// Render rect
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::Draw()
{
	SDL_RenderPresent(renderer);
}

void Graphics::ClearScreen()
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);
}

void Graphics::Sleep(int ms)
{
	SDL_Delay(ms);
}

void Graphics::Exit()
{
	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
}