#include "input.h"

void doKeyUp(SDL_KeyboardEvent *event) {
	if (event->keysym.scancode == SDL_SCANCODE_ESCAPE) {
		exit(0);
	}
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app.keyboard[event->keysym.scancode] = 0;
	}
}

void doKeyDown(SDL_KeyboardEvent *event) {
	if (event->keysym.scancode == SDL_SCANCODE_ESCAPE) {
		exit(0);
	}
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app.keyboard[event->keysym.scancode] = 1;
	}
}

void doInput(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
}
