#ifndef GAME_H
#define GAME_H

#include "window.h"
#include <raylib.h>

struct Grid
{
	int size;
	Color **color;
};

void mainLoop(struct Window *window);

#endif