#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int w, int h, double angle);
extern SDL_Texture *loadTexture(char *filename);

class Spaceship {
	public:
		Spaceship(int x, int y, int w, int h);

		~Spaceship();

        Spaceship(const Spaceship&);
        Spaceship operator=(const Spaceship&);

		void loadSprite(const std::string &image_path);
		void draw() const;

		void turn(double dangle);
		bool isAlive();

	private:
		int x, y;		// position (coordinates)
		int w, h;		// width and height of displayed texture
		float dx, dy;	// velocity
		double angle;	// angle in degrees
		bool alive;
		SDL_Texture *texture = nullptr;
};
