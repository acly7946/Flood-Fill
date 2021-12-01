#ifndef GAME_H
#define GAME_H

#include "window.h"
#include <raylib.h>

struct Grid
{
	int cols;
	int rows;
	Color **color;
};

void mainLoop(struct Window *window);

#endif