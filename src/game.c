#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

#define MARGIN 9
#define GAP 3

static void initGrid(struct Grid *grid, int size);
static void fillAdjacent(struct Grid *grid, int row, int col, int oldColor, int newColor);

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

		if(IsMouseButtonPressed(0)) // left mouse button
		{
			selectionX = GetMouseX() / spacingX;
			selectionY = GetMouseY() / spacingY;
			if((selectionX < grid.size) && (selectionY < grid.size)) // within window boundaries
			{
				if((selectionX >= 0) && (selectionY >= 0))
				{
					fillAdjacent(&grid, selectionX, selectionY, grid.color[selection3X][selectionY], 0); // fill with red for now
				}
			}
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);
			for(int row = 0; row < grid.size; row++)
			{
				for(int col = 0; col < grid.size; col++)
				{
					switch(grid.color[row][col])
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
					cell = (Rectangle){spacingX*row + MARGIN, spacingY*col + MARGIN, spacingX - GAP, spacingY - GAP};
					DrawRectangleRounded(cell, 0.1, 1, color);
					DrawRectangleRoundedLines(cell, 0.1, 1, 1, BLACK);
				}
			}
		EndDrawing();
	}
	free(grid.color);
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
	for(int row = 0; row < size; row++)
	{
		for(int col = 0; col < size; col++)
		{
			grid->color[row][col] = rand()%6;
		}
	}
}

static void fillAdjacent(struct Grid *grid, int row, int col, int oldColor, int newColor)
{
	/*
	Checks adjacent cells in this order:
	[ ][1][ ]
	[4][0][2]
	[ ][3][ ]
	will recurse for each matching color
	and fill oldColor with newColor
	*/

	int checkRow = row; // The positions we're checking currently
	int checkCol = col;
	struct // vectors for checking adjacent cells
	{
		int dx;
		int dy;
	}	adjacent[] = {{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	for(int i = 0; i < 5; i++)
	{
		checkRow = row + adjacent[i].dx;
		checkCol = col + adjacent[i].dy;
		if((checkRow < grid->size) && (checkCol < grid->size)) // within window boundaries
		{
			if((checkRow >= 0) && (checkCol >= 0))
			{
				if(grid->color[checkRow][checkCol] == oldColor)
				{
					grid->color[checkRow][checkCol] = newColor;
					fillAdjacent(grid, checkRow, checkCol, oldColor, newColor);
				}
			}
		}
	}
}