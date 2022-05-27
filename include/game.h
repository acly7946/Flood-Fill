#ifndef GAME_H
#define GAME_H

#include "window.h"
#include <raylib.h>

struct Grid
{
	int size;
	int **color;
};

void mainLoop(struct Window *window);

#endif