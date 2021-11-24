#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

static void initGrid(struct Grid *grid);

void mainLoop(struct Window *window)
{
    int gapX;
    int gapY;
    Color color;
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
        gapX = (window->width)/grid.cols;
        gapY = (window->height)/grid.rows;

        BeginDrawing();
            ClearBackground(WHITE);
            for(int i = 0; i < grid.rows; i++)
            {
                for(int j = 0; j < grid.cols; j++)
                {
                    switch(grid.data[i][j])
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
                    DrawRectangle(gapX*i, gapY*j, gapX - 3, gapY - 3, color); // 3 is spacing
                }
            }
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