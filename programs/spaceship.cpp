#include "../classes/spaceship.h"


Spaceship::Spaceship(const Window &win, int wIn, int hIn, int xIn, int yIn, const std::string &image_path) : Window(win), w(wIn), h(hIn), x(xIn), y(yIn)
{
	SDL_Surface *surface = IMG_Load(image_path.c_str());
	if(!surface) {
		std::cout << "failed to create surface\n";
		std::cout << IMG_GetError() << std::endl;
		std::cout << image_path.c_str() << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if(!texture) {
		std::cout << "failed to load texture\n";
	}

	SDL_FreeSurface(surface);

}

Spaceship::~Spaceship() {
	SDL_DestroyTexture(texture);
}

void Spaceship::draw() const {
	SDL_Rect spaceship = {x, y, w, h};

	if(texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &spaceship);
	}
}

void Spaceship::pollEvents(SDL_Event &event) {
	if(event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_LEFT:
				x -= 10;
				break;
			case SDLK_RIGHT:
				x += 10;
				break;
			case SDLK_UP:
				y -= 10;
				break;
			case SDLK_DOWN:
				y += 10;
				break;
			default:
				break;
		}
	}
}
