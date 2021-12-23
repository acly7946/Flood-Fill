#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

#define MARGIN 9
#define GAP 3

static void initGrid(struct Grid *grid, int size);
static void fillAdjacent(struct Grid *grid, int currentX, int currentY);

void mainLoop(struct Window *window)
{
	int spacingX;
	int spacingY;
	Rectangle cell;
	Color color;
	struct Grid grid;
	int selectionX = 0;
	int selectionY = 0;

	initGrid(&grid, 15);

	while(!WindowShouldClose())
	{
		window->frameTime = GetFrameTime();
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();
		spacingX = (window->width - MARGIN)/grid.size;
		spacingY = (window->height - MARGIN)/grid.size;

		if(IsMouseButtonDown(0)) // left mouse button
		{
			selectionX = GetMouseX() / spacingX;
			selectionY = GetMouseY() / spacingY;
			if((selectionX < grid.size) && (selectionY < grid.size)) // within window boundaries
			{
				if((selectionX >= 0) && (selectionY >= 0))
				{
					fillAdjacent(&grid, selectionX, selectionY);
				}
			}
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);
			for(int col = 0; col < grid.size; col++)
			{
				for(int row = 0; row < grid.size; row++)
				{
					switch(grid.color[col][row])
					{
						case 0:
							color = RED;
							break;
						case 1:
							color = ORANGE;
							break;
						case 2:
							color = YELLOW;
							break;
						case 3:
							color = GREEN;
							break;
						case 4:
							color = BLUE;
							break;
						case 5:
							color = VIOLET;
							break;
					}
					cell = (Rectangle){spacingX*col + MARGIN, spacingY*row + MARGIN, spacingX - GAP, spacingY - GAP};
					DrawRectangleRounded(cell, 0.1, 1, color);
					DrawRectangleRoundedLines(cell, 0.1, 1, 1, BLACK);
				}
			}
		EndDrawing();
	}
}

static void initGrid(struct Grid *grid, int size)
{
	grid->size = size;
	// Create 1D array, then convert to 2D
	int *data1D = (int*)malloc(size * size * sizeof(int));
	grid->color = (int**)malloc(size * size * sizeof(int*));

	for(int i = 0; i < size; i++)
	{
		grid->color[i] = data1D + (i * size);
	}

	// Fill with random colors from 1-6
	for(int col = 0; col < size; col++)
	{
		for(int row = 0; row < size; row++)
		{
			grid->color[col][row] = rand()%6;
		}
	}
}

static void fillAdjacent(struct Grid *grid, int currentX, int currentY)
{
	/*
	Checks adjacent cells in this order:
	[ ][2][ ]
	[1][ ][3]
	[ ][4][ ]
	will recurse for each matching color
	*/

	int checkingX = currentX;
	int checkingY = currentY;
	struct // vectors for checking adjacent cells
	{
		int dx;
		int dy;
	}	adjacent[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	grid->color[checkingX][checkingY] = 0;
	for(int i = 0; i < 4; i++)
	{
		checkingX = currentX + adjacent[i].dx;
		checkingY = currentY + adjacent[i].dy;

		if((checkingX < grid->size) && (checkingY < grid->size)) // within window boundaries
		{
			if((checkingX >= 0) && (checkingY >= 0))
			{
				if(grid->color[checkingX][checkingY] == 1) // 0 = RED
				{
					grid->color[checkingX][checkingY] = 0;
					fillAdjacent(grid, checkingX, checkingY);
				}
			}
		}
	}
}