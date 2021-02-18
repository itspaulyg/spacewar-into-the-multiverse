#include "../classes/spaceship.h"

void pollEvents(Window &window, Spaceship &spaceship1) {
	SDL_Event event;

// need to add movement and events for spaceship2
	if(SDL_PollEvent(&event)) {
		spaceship1.pollEvents(event);
		window.pollEvents(event);
	}
}

int main() {

	Window window("Spacewar! Into the Multiverse", 1200, 900);
	Spaceship spaceship1(window, 30, 45, 100, 100, 0, 0, 0, 0, "rocketship.png");
	Spaceship spaceship2(window, 20, 50, 500, 500, 0, 0, 0, 0, "verticalrocket.png");

	while(!window.isClosed()) {
		pollEvents(window, spaceship1);
		spaceship1.draw();
		spaceship2.draw();
		window.clear();
	}

	return 0;

}
