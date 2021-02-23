#include "spaceship.h"

void check_boundaries(int, int);

Spaceship::Spaceship(int xIn, int yIn, int wIn, int hIn) :
		x((double) xIn), y((double) yIn), w(wIn), h(hIn), dx(0), dy(0), angle(0), alive(true) { }

Spaceship::~Spaceship() {
	SDL_DestroyTexture(texture);
}

void Spaceship::loadSprite(const std::string &image_path) {
	texture = loadTexture(const_cast<char*>(image_path.c_str()));
}

void Spaceship::draw() const {
	blit(texture, (int) round(x), (int) round(y), w, h, angle);
}

void Spaceship::turn(double dangle) {
	angle += dangle;
	if (angle > 360) {
		angle -= 360;
	}
	if (angle < -360) {
		angle += 360;
	}
	printf("%f\n", angle);
}

void Spaceship::thrust(double force) {
	dx += (cos(angle * (PI / 180.0)) * force);
	dy += (sin(angle * (PI / 180.0)) * force);
	printf("dx: %f\t dy: %f\n", dx, dy);
}

void Spaceship::move() {
	x += dx * TICK;
	y += dy * TICK;
	return;
}

bool Spaceship::isAlive() {
	return alive;
}

/*
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
*/
