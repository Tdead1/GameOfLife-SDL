#pragma once

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

#include <utility>

enum class KEY
{
	NONE = 0
	, ESC = 27
	, SPACE = 32
	, MOUSELEFT = 1025
};

class Graphics
{
public:
	void Init();
	
	KEY GetInput();
	std::pair<int, int> GetMousePosition();

	void DrawRectangle(const int x, const int y, const int sizex, const int sizey);
	void Draw();
	void ClearScreen();
	void Sleep(int ms);
	void Exit();

private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
};