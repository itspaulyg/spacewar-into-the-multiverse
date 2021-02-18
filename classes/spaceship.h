#include "window.h"
#include <math.h>

class Spaceship : public Window {
	public:
		Spaceship(const Window &window, int w, int h, int x, int y, const std::string &image_path);
		~Spaceship();

        Spaceship(const Spaceship&);
        Spaceship operator=(const Spaceship&);

		void draw() const;
		void pollEvents(SDL_Event &event);

	private:
		int w, h;
		int x, y;
		SDL_Texture *texture = nullptr;
};
