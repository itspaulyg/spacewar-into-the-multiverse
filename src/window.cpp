#include "window.h"

void initSDL(const std::string &title, int width, int height) {
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_PRESENTVSYNC;	// Available Flags: https://wiki.libsdl.org/SDL_RendererFlags
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("Couldn't initialize IMG: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);

	if (!app.window) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	return;
}

void clearSDL() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
	SDL_RenderPresent(app.renderer);
}

void cleanup() {
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}