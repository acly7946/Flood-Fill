#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

static void initGrid(struct Grid *grid);

void mainLoop(struct Window *window)
{
    struct Grid grid =
    {
        .cols = 15,
        .rows = 15,
        .data = NULL
    };
    initGrid(&grid);

    while(!WindowShouldClose())
    {
        window->frameTime = GetFrameTime();
        window->width = GetScreenWidth();
        window->height = GetScreenHeight();

        BeginDrawing();
            ClearBackground(WHITE);
        EndDrawing();
    }
}

static void initGrid(struct Grid *grid)
{
    // Create 1D array, then convert to 2D
    int *data1D = (int*)malloc(grid->rows * grid->cols * sizeof(int));
    grid->data = (int**)malloc(grid->rows * grid->cols * sizeof(int*));

    for(int i = 0; i < grid->rows; i++)
    {
        grid->data[i] = data1D + (i * grid->cols);
    }

    // Fill with random nums from 1-6
    for(int i = 0; i < grid->rows; i++)
    {
        for(int j = 0; j < grid->cols; j++)
        {
            grid->data[i][j] = rand()%6;
        }
    }
}