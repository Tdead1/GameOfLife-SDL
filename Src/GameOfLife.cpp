#include "GameOfLife.h"
#include "Graphics.h"

#include <iostream>
#include <vector>
#include <unordered_map>

struct Point
{
	bool operator==(const Point& pointA) { return x == pointA.x && y == pointA.y; };
	int32_t x = 0;
	int32_t y = 0;
	bool alive = false;
};

void GameOfLife::Run(Graphics& graphics)
{
	// Plug in any starting points here.
	// Some examples: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
	std::vector<std::pair<int32_t, int32_t>> startingPoints =
	{
		// Beacon
		  {1 + 3, 1 + 0}
		, {2 + 3, 1 + 0}
		, {1 + 3, 2 + 0}
		, {4 + 3, 3 + 0}
		, {4 + 3, 4 + 0}
		, {3 + 3, 4 + 0}

		// Spaceship
		, {0 + 5, 12 + 10}
		, {1 + 5, 10 + 10}
		, {1 + 5, 12 + 10}
		, {2 + 5, 11 + 10}
		, {2 + 5, 12 + 10}

		// Spaceship
		, {0 + 15, 12 + 15}
		, {1 + 15, 10 + 15}
		, {1 + 15, 12 + 15}
		, {2 + 15, 11 + 15}
		, {2 + 15, 12 + 15}

		// Spaceship
		, {0 + 50, 12 + 5}
		, {1 + 50, 10 + 5}
		, {1 + 50, 12 + 5}
		, {2 + 50, 11 + 5}
		, {2 + 50, 12 + 5}

		// Spaceship
		, {0 + 10, 12 + 10}
		, {1 + 10, 10 + 10}
		, {1 + 10, 12 + 10}
		, {2 + 10, 11 + 10}
		, {2 + 10, 12 + 10}

		// Spaceship
		, {0 + 15, 12 + 10}
		, {1 + 15, 10 + 10}
		, {1 + 15, 12 + 10}
		, {2 + 15, 11 + 10}
		, {2 + 15, 12 + 10}

		// Box
		, {1 + 25, 1 + 25}
		, {1 + 25, 2 + 25}
		, {2 + 25, 1 + 25}
		, {2 + 25, 2 + 25}

		// Box
		, {1 + 50, 1 + 25}
		, {1 + 50, 2 + 25}
		, {2 + 50, 1 + 25}
		, {2 + 50, 2 + 25}

		// Box
		, {1 + 60, 1 + 25}
		, {1 + 60, 2 + 25}
		, {2 + 60, 1 + 25}
		, {2 + 60, 2 + 25}
	};

	std::vector<Point> points;
	std::vector<Point> modifiedPoints;
	
	int32_t sizex = 120;
	int32_t sizey = 30;
	
	for (int32_t i = 0; i < sizey; i++)
	{
		for (int32_t j = 0; j < sizex; j++)
		{
			if (std::find(startingPoints.begin(), startingPoints.end(), std::pair<int32_t, int32_t>{ j, i }) != startingPoints.end())
				points.emplace_back(j, i, true);
			else
				points.emplace_back(j, i, false);
		}
	}

	int32_t x;
	int32_t y;

	auto GetNeighborPoint = [&](int32_t ax, int32_t ay) {
		if (ax < 0 || ax >= sizex || ay < 0 || ay >= sizey) return points.end();
		return (points.begin() + ((ay * sizex) + ax));
	};

	auto GetPoint = [&]() {
		if (x < 0 || x >= sizex || y < 0 || y >= sizey) return points.end();
		return (points.begin() + ((y * sizex) + x));
	};

	auto GetPointToModify = [&]() {
		if (x < 0 || x >= sizex || y < 0 || y >= sizey) return modifiedPoints.end();
		return (modifiedPoints.begin() + ((y * sizex) + x));
	};

	auto GetNeighbors = [&]()
	{
		int8_t count = 0;
		for (int8_t i = -1; i < 2; i++)
		{
			for (int8_t j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0) continue;
				auto p = GetNeighborPoint(x + j, y + i);
				if (p != points.end() && p->alive)
					count++;
				else continue;
			}
		}

		return count;
	};

	auto GetSetAliveness = [&]()
	{
		auto p = GetPointToModify();
		if (p != modifiedPoints.end())
		{
			int8_t neighbors = GetNeighbors();
			p->alive = p->alive ? (neighbors == 2 || neighbors == 3) : neighbors == 3;
			return p->alive;
		}
		return false;
	};

	for (y = 0; y < sizey; y++)
	{
		for (x = 0; x < sizex; x++)
		{
			if(GetPoint()->alive)
			{
				graphics.DrawRectangle(x * 10, y * 10, 10, 10);
			}
		}
	}

	while (graphics.GetInput() != KEY::ESC)
	{
		graphics.ClearScreen();
		modifiedPoints = points;
		for (y = 0; y < sizey; y++)
		{
			for (x = 0; x < sizex; x++)
			{
				if (GetSetAliveness())
				{
					graphics.DrawRectangle(x * 10, y * 10, 10, 10);
				}
			}
		}
		points = modifiedPoints;

		graphics.Draw();
		graphics.Sleep(67);
	}
}