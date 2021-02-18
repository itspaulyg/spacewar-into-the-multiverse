#include "../classes/spaceship.h"

void pollEvents(Window &window, Spaceship &spaceship) {
	SDL_Event event;

	if(SDL_PollEvent(&event)) {
		spaceship.pollEvents(event);
		window.pollEvents(event);
	}
}

int main() {

	Window window("Tutorial", 800, 600);
	Spaceship spaceship(window, 10, 10, 100, 100, "rocketship.png");

	while(!window.isClosed()) {
		pollEvents(window, spaceship);
		spaceship.draw();
		window.clear();
	}

	return 0;

}
