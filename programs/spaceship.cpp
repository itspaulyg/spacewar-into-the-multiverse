#include "../classes/spaceship.h"

void check_boundaries(int, int);

Spaceship::Spaceship(const Window &win, int wIn, int hIn, int xIn, int yIn, int xVelIn, int yVelIn, int wVelIn, double deg, const std::string &image_path) : Window(win), w(wIn), h(hIn), x(xIn), y(yIn), xVel(xVelIn), yVel(yVelIn), wVel(wVelIn), degree(deg)
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
		SDL_RenderCopyEx(renderer, texture, nullptr, &spaceship, degree, NULL, SDL_FLIP_NONE);
	}
}

void Spaceship::pollEvents(SDL_Event &event) {

//need to add acceleration on keydown
	if(event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_LEFT:
				degree -= 10;
				break;
			case SDLK_RIGHT:
				degree += 10;
				break;
			case SDLK_UP:
				x += int(10*sin(degree * PI / 180));
				y -= int(10*cos(degree * PI / 180));
				check_boundaries(x, y);
				break;
			case SDLK_DOWN:
				x = rand()%500 + 50;
				y = rand()%500 + 50;
//				SDL_Delay(3000); not sure if this can be used for hyperspace delay
				break;
			default:
				break;
		}
	}

// need to add deceleration on keyup
	if(event.type == SDL_KEYUP) {
		switch(event.key.keysym.sym) {
			case SDLK_UP:
				x += int(10*sin(degree * PI / 180));
				y -= int(10*cos(degree * PI / 180));
				check_boundaries(x, y);
				break;
			default:
				break;
		}
	}
}

// need to determine how to check boundaries correctly
void check_boundaries(int x, int y) {
	if(y >= 1080) {
		y = 0;
	}
	else if(y <= 0) {
		y = 1080;
	}
	if(x >= 920) {
		x = 0;
	}
	else if(x <= 0) {
		x = 920;
	}
}
