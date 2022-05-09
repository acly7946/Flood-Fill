#include "game.h"
#include "window.h"
#include <getopt.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM "floodfill"
#define VERSION "0.2.0"
#define AUTHOR "acly7946"
#define LICENSE "MIT"
#define MSAA_OPT 1000 /* long-only opts */
#define VSYNC_OPT 1001

struct Options
{
	int msaa;
	int vsync;
};

static void usage(void);
static void version(void);
static void initGame(struct Window *window, struct Options *options);

int main(int argc, char *argv[])
{
	int optc;
	struct Window window;
	struct Options options = /* defaults */
	{
		.msaa = 0,
		.vsync = 1
	};
	static struct option long_options[] =
	{
		{"msaa", optional_argument, NULL, MSAA_OPT},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'V'},
		{"vsync", optional_argument, NULL, VSYNC_OPT},
	};
	while((optc = getopt_long(argc, argv, "hV", long_options, NULL)) != EOF)
	{
		switch(optc)
		{
			case MSAA_OPT:
				if(!(sscanf(optarg, "%d", &options.msaa)))
				{
					fprintf(stderr, "--msaa must be set to either 1 or 0");
					usage();
				}
				break;

			case VSYNC_OPT:
				if(!(sscanf(optarg, "%d", &options.vsync)))
				{
					fprintf(stderr, "--vsync must be set to either 1 or 0");
					usage();
				}
				break;

			case 'V':
				version();

			default:
				usage();
		}
	}

	initGame(&window, &options);
	mainLoop(&window);

	CloseAudioDevice();
	CloseWindow();
	return EXIT_SUCCESS;
}

static void usage(void)
{
	fprintf(stderr,
	"Usage: %s [OPTIONS]\n"
	"\n"
	"  -h, --help	 Print this help message and immediately quit\n"
	"  -V, --version  Print version number and immediately quit\n"
	"\n"
	"  --msaa=[0|1]   Set anti-aliasing (default: 0)\n"
	"  --vsync=[0|1]  Set vsync (default: 1)\n"
	, PROGRAM);
	exit(EXIT_FAILURE);
}

static void version(void)
{
	printf(
	"%s %s\n"
	"Copyright (c) 2022 %s\n"
	"%s License\n"
	, PROGRAM, VERSION, AUTHOR, LICENSE);
	exit(EXIT_SUCCESS);
}

static void initGame(struct Window *window, struct Options *options)
{
	window->width = 650,
	window->height = 600;

	if(options->msaa)
	{
		SetConfigFlags(FLAG_MSAA_4X_HINT);
	}
	if(options->vsync)
	{
		SetConfigFlags(FLAG_VSYNC_HINT);
	}

	srand((unsigned)time(NULL));
	InitWindow(window->width, window->height, "Flood Fill");
	InitAudioDevice();
}