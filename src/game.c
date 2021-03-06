#include "game.h"
#include "window.h"
#include <errno.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define MARGIN 9

static int initGrid(struct Grid *grid, int size);
static void floodFill(struct Grid *grid, int row, int col, int oldColor, int newColor);
static void renderGrid(struct Window window, struct Grid grid);
static void renderUI(struct Window window, int turns);
static void handleInput(struct Window window, struct Grid *grid, int *turns);
static Color getColor(int num);

void mainLoop(struct Window *window)
{
	struct Grid grid;
	int turns = 25;

	if(initGrid(&grid, 14) != 0)
	{
		perror("\nERROR(game.c, initGrid): Failed to initialize grid");
		exit(EXIT_FAILURE);
	}

	while(!WindowShouldClose())
	{
		window->frameTime = GetFrameTime();
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();

		if(turns)
		{
			handleInput(*window, &grid, &turns);
		}

		BeginDrawing();
			renderGrid(*window, grid);
			renderUI(*window, turns);
		EndDrawing();
	}
	free(grid.color);
}

static int initGrid(struct Grid *grid, int size)
{
	/* Create 1D array, then convert to 2D */
	grid->size = size;
	int *data1D = malloc(size * size * sizeof(size));
	grid->color = malloc(size * size * sizeof(size));

	if((data1D == NULL) || (grid->color == NULL))
	{
		free(data1D);
		return -1;
	}

	for(int i = 0; i < size; i++)
	{
		grid->color[i] = data1D + (i * size);
	}

	/* Fill with random colors from 1-6 */
	for(int row = 0; row < size; row++)
	{
		for(int col = 0; col < size; col++)
		{
			grid->color[row][col] = rand()%6;
		}
	}

	return 0;
}

static void floodFill(struct Grid *grid, int row, int col, int oldColor, int newColor)
{
	/*
	Checks adjacent cells in this order:
	[ ][1][ ]
	[4][ ][2]
	[ ][3][ ]
	will recurse for each matching color
	and fill oldColor with newColor
	*/

	int checkRow; /* The positions we're checking currently */
	int checkCol;
	struct /* vectors for checking adjacent cells */
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
			if((checkRow < grid->size) && (checkCol < grid->size)) /* within window boundaries */
			{
				if((checkRow >= 0) && (checkCol >= 0))
				{
					if(grid->color[checkRow][checkCol] == oldColor)
					{
						grid->color[checkRow][checkCol] = newColor;
						floodFill(grid, checkRow, checkCol, oldColor, newColor);
					}
				}
			}
		}
	}
}

static void renderGrid(struct Window window, struct Grid grid)
{
	int spacing;
	Rectangle cell;
	Color color;

	if(window.width < window.height)
	{
		spacing = (window.width-MARGIN*2)/grid.size;
	}
	else
	{
		spacing = (window.height-MARGIN*2)/grid.size;
	}

	ClearBackground(RAYWHITE);
	/* cells */
	for(int row = 0; row < grid.size; row++)
	{
		for(int col = 0; col < grid.size; col++)
		{
			color = getColor(grid.color[row][col]);
			cell = (Rectangle){(float)(MARGIN+spacing*row), (float)(MARGIN+spacing*col), (float)spacing, (float)spacing};
			DrawRectangleRec(cell, color);
		}
	}
	/* outline */
	DrawRectangleLines(MARGIN, MARGIN, grid.size*spacing, grid.size*spacing, BLACK);
}

static void renderUI(struct Window window, int turns)
{
	if(window.width > window.height)
	{
		DrawText(TextFormat("%d", turns), window.width - 60, 9, 50, BLACK);
	}
	else
	{
		DrawText(TextFormat("%d", turns), 9, window.height-60, 50, BLACK);
	}
}

static void handleInput(struct Window window, struct Grid *grid, int *turns)
{
	int spacing;
	int selectionX;
	int selectionY;
	int keyPress;

	if(window.width < window.height)
	{
		spacing = (window.width)/grid->size;
	}
	else
	{
		spacing = (window.height)/grid->size;
	}

	if(IsMouseButtonPressed(0)) /* left mouse button */
	{
		selectionX = GetMouseX()/spacing;
		selectionY = GetMouseY()/spacing;
		if((selectionX < grid->size) && (selectionY < grid->size)) /* within window boundaries */
		{
			if((selectionX >= 0) && (selectionY >= 0))
			{
				if(grid->color[0][0] != grid->color[selectionX][selectionY])
				{
					/* free-flood-fill */
					/* floodFill(&grid, selectionX, selectionY, grid.color[selectionX][selectionY], 0); */
					floodFill(grid, 0, 0, grid->color[0][0], grid->color[selectionX][selectionY]); /* normal flood-fill */
					*turns-=1;
				}
			}
		}
	}
	switch(GetKeyPressed())
	{
		case KEY_ONE:
			keyPress = 0;
			break;
		case KEY_TWO:
			keyPress = 1;
			break;
		case KEY_THREE:
			keyPress = 2;
			break;
		case KEY_FOUR:
			keyPress = 3;
			break;
		case KEY_FIVE:
			keyPress = 4;
			break;
		case KEY_SIX:
			keyPress = 5;
			break;
		default:
			keyPress = -1;
			break;

	}
	if(keyPress >= 0)
	{
		floodFill(grid, 0, 0, grid->color[0][0], keyPress);
		*turns-=1;
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
			fprintf(stderr, "\nERROR(game.c, getColor): Invalid color number: %d\n\n", num);
			exit(EXIT_FAILURE);
	}
}
