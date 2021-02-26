#include "main.h"

int main() {
	memset(&app, 0, sizeof(App));

	initSDL("Spacewar! Into the Multiverse", SCREEN_WIDTH, SCREEN_HEIGHT);

	atexit(cleanup);

	initSpace();

	while(!startGame()) {
		mainScreen();
	}

	while(1) {
		prepareScene();

		doInput();

		app.delegate.logic();

		app.delegate.draw();
		
		presentScene();
	}

	return 0;
}
