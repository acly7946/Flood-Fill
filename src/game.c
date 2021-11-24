#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

static void initGrid(struct Grid *grid, int cols, int rows);

void mainLoop(struct Window *window)
{
    int gapX;
    int gapY;
    Color color;
    Rectangle cell;
    struct Grid grid;
    initGrid(&grid, 15, 15);

    while(!WindowShouldClose())
    {
        window->frameTime = GetFrameTime();
        window->width = GetScreenWidth();
        window->height = GetScreenHeight();
        gapX = (window->width)/grid.cols; // spacing between cells
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
                    cell = (Rectangle){gapX*i, gapY*j, gapX - 3, gapY - 3}; // 3 is spacing
                    DrawRectangleRec(cell, color);
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