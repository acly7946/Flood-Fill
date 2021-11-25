#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

static void initGrid(struct Grid *grid, int cols, int rows);

void mainLoop(struct Window *window)
{
	int spacingX;
	int spacingY;
	int selectionX;
	int selectionY;
	Color color;
	Rectangle cell;
	struct Grid grid;

	initGrid(&grid, 20, 20);

	while(!WindowShouldClose())
	{
		window->frameTime = GetFrameTime();
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();
		spacingX = (window->width)/grid.cols;
		spacingY = (window->height)/grid.rows;

		if(IsMouseButtonDown(0)) // left mouse button
		{
			selectionX = GetMouseX() / spacingX;
			selectionY = GetMouseY() / spacingY;
		}

		BeginDrawing();
			ClearBackground(WHITE);
			for(int col = 0; col < grid.cols; col++)
			{
				for(int row = 0; row < grid.rows; row++)
				{
					switch(grid.data[col][row])
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
					cell = (Rectangle){spacingX*col, spacingY*row, spacingX - 3, spacingY - 3}; // 3 is spacing
					DrawRectangleRec(cell, color);
					if((col == selectionX) && (row == selectionY))
					{
						DrawRectangleLinesEx(cell, 5, BLACK);
					}
				}
			}
		EndDrawing();
	}
}

static void initGrid(struct Grid *grid, int cols, int rows)
{
	// Create 1D array, then convert to 2D
	int *data1D = (int*)malloc(rows * cols * sizeof(int));
	grid->data = (int**)malloc(rows * cols * sizeof(int*));
	grid->cols = cols;
	grid->rows = rows;

	for(int i = 0; i < rows; i++)
	{
		grid->data[i] = data1D + (i * cols);
	}

	// Fill with random nums from 1-6
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			grid->data[i][j] = rand()%6;
		}
	}
}
