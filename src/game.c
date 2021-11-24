#include "game.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

void mainLoop(struct Window *window)
{
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