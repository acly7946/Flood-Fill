#include "game.h"
#include "window.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static void initGrid(struct Grid *grid, int size);
static void fillAdjacent(struct Grid *grid, int row, int col, int oldColor, int newColor);
static void renderGrid(struct Window *window, struct Grid *grid);
static void handleInput(struct Window *window, struct Grid *grid);
static Color getColor(int num);

void mainLoop(struct Window *window)
{
	struct Grid grid;

	initGrid(&grid, 14);

	while(!WindowShouldClose())
	{
		window->frameTime = GetFrameTime();
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();

		renderGrid(window, &grid);
		handleInput(window, &grid);

	}
	free(grid.color);
}

static void initGrid(struct Grid *grid, int size)
{
	free(grid->color); // if done again with smaller value
	// Create 1D array, then convert to 2D
	grid->size = size;
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
	[4][ ][2]
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
	}	adjacent[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	if(oldColor != newColor)
	{
		grid->color[row][col] = newColor;
		for(int i = 0; i < 4; i++)
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
}

static void renderGrid(struct Window *window, struct Grid *grid)
{
	int spacing;
	Rectangle cell;
	Color color;

	if(window->width < window->height)
	{
		spacing = (window->width)/grid->size;
	}
	else
	{
		spacing = (window->height)/grid->size;
	}

	BeginDrawing();
		ClearBackground(RAYWHITE);
		for(int row = 0; row < grid->size; row++)
		{
			for(int col = 0; col < grid->size; col++)
			{
				color = getColor(grid->color[row][col]);
				cell = (Rectangle){spacing*row, spacing*col, spacing, spacing};
				DrawRectangleRec(cell, color);
			}
		}
	EndDrawing();
}

static void handleInput(struct Window *window, struct Grid *grid)
{
	int spacing;
	int selectionX = 0;
	int selectionY = 0;

	if(window->width < window->height)
	{
		spacing = (window->width)/grid->size;
	}
	else
	{
		spacing = (window->height)/grid->size;
	}

	if(IsMouseButtonPressed(0)) // left mouse button
	{
		selectionX = (int)round(GetMouseX()/spacing);
		selectionY = (int)round(GetMouseY()/spacing);
		if((selectionX < grid->size) && (selectionY < grid->size)) // within window boundaries
		{
			if((selectionX >= 0) && (selectionY >= 0))
			{
				//fillAdjacent(&grid, selectionX, selectionY, grid.color[selectionX][selectionY], 0); // free-flood-it
				fillAdjacent(grid, 0, 00, grid->color[0][0], grid->color[selectionX][selectionY]); // normal flood-it
			}
		}
	}
}

static Color getColor(int num)
{
	switch(num)
	{
		case 0:
			return RED;
		case 1:
			return ORANGE;
		case 2:
			return YELLOW;
		case 3:
			return GREEN;
		case 4:
			return BLUE;
		case 5:
			return VIOLET;
		default:
			fprintf(stderr, "ERROR(game.c, getColor): Invalid color number: %d", num);
			exit(EXIT_FAILURE);
	}
}