#include "screen.h"

bool startGame();
void mainScreen();

bool startGame() {

	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
					exit(0);
					break;
				case SDLK_SPACE:
					return true;
				default:
					return false;
					break;
			}
		}
	}

	return false;
}

void mainScreen() {
	prepareScene();
	static SDL_Texture *main_screen_texture = loadTexture((char *)"./mainscreen.png");
	SDL_RenderCopy(app.renderer, main_screen_texture, NULL, NULL);
	presentScene();
}
