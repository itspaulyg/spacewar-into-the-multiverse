#include "window.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159

class Spaceship : public Window {
	public:
		Spaceship(const Window &window, int w, int h, int x, int y, int xVel, int yVel, int wVel, double degrees, const std::string &image_path);
		~Spaceship();

        Spaceship(const Spaceship&);
        Spaceship operator=(const Spaceship&);

		void draw() const;
		void pollEvents(SDL_Event &event);

	private:
		int w, h;
		int x, y;
		int xVel, yVel, wVel;
		double degree;
		SDL_Texture *texture = nullptr;
};
