#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

#define MARGIN 10
#define GAP 1

static void initGrid(struct Grid *grid, int cols, int rows);

void mainLoop(struct Window *window)
{
	int spacingX;
	int spacingY;
	Rectangle cell;
	struct Grid grid;
	int selectionX = 0;
	int selectionY = 0;

	initGrid(&grid, 10, 20);

	while(!WindowShouldClose())
	{
		window->frameTime = GetFrameTime();
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();
		spacingX = (window->width - MARGIN)/grid.cols;
		spacingY = (window->height - MARGIN)/grid.rows;

		if(IsMouseButtonDown(0)) // left mouse button
		{
			selectionX = GetMouseX() / spacingX;
			selectionY = GetMouseY() / spacingY;
			grid.color[selectionX][selectionY] = RED;
		}

		BeginDrawing();
			ClearBackground(WHITE);
			for(int col = 0; col < grid.cols; col++)
			{
				for(int row = 0; row < grid.rows; row++)
				{
					cell = (Rectangle){spacingX*col + MARGIN, spacingY*row + MARGIN, spacingX - GAP, spacingY - GAP};
					DrawRectangleRec(cell, grid.color[col][row]);
					DrawText(TextFormat("col: %d", col), spacingX*col + 10, spacingY*row + 10, 20, PINK);
					DrawText(TextFormat("row: %d", row), spacingX*col + 10, spacingY*row + 30, 20, PINK);
				}
			}
		EndDrawing();
	}
}

static void initGrid(struct Grid *grid, int cols, int rows)
{
	Color color;
	grid->cols = cols;
	grid->rows = rows;
	// Create 1D array, then convert to 2D
	Color *data1D = (Color*)malloc(rows * cols * sizeof(int));
	grid->color = (Color**)malloc(rows * cols * sizeof(int*));

	for(int i = 0; i < rows; i++)
	{
		grid->color[i] = data1D + (i * cols);
	}

	// Fill with random colors from 1-6
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			switch(rand()%6)
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
			grid->color[i][j] = color;
		}
	}
}