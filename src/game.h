#ifndef GAME_H
#define GAME_H

#include "window.h"

struct Grid
{
	int cols;
	int rows;
	int **data;
};

void mainLoop(struct Window *window);

#endif