 // Game of life.
#include "Graphics.h"
#include "GameOfLife.h"

int main()
{
	Graphics graphics;
	graphics.Init();

	GameOfLife::Run(graphics);

	graphics.Exit();
	return 0;
}