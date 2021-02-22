#include "space.h"

static void logic();
static void draw();
static void doShips();
static void fireBullet(Spaceship s);
// static void doWedge();
// static void doNeedle();
// static void doWedgeFire();
// static void doNeedleFire();
// static void drawBullets();
// static void bulletHitShip();
// static void shipHitShip();
// static void shipHitSun();
// static void doGravity();

static Spaceship wedge(WEDGE_X, WEDGE_Y, WEDGE_W, WEDGE_H);
static Spaceship needle(NEEDLE_X, NEEDLE_Y, NEEDLE_W, NEEDLE_H);
static SDL_Texture *bulletTexture;

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    wedge.loadSprite("./wedge.png");
    needle.loadSprite("./needle.png");
    bulletTexture = loadTexture(const_cast<char*>("bullet.png"));
}

static void logic() {
    doShips();
}

static void doShips() {
    if (wedge.isAlive()) {
        if (app.keyboard[SDL_SCANCODE_A]) {     // turn CCW
            wedge.turn(-TURNSPEED);
            printf("A\n");
        }
        if (app.keyboard[SDL_SCANCODE_D]) {     // turn CW
            wedge.turn(TURNSPEED);
            printf("D\n");
        }
        if (app.keyboard[SDL_SCANCODE_S]) {     // thrust
            wedge.thrust(THRUSTFORCE);
            printf("Thrusting...\n");
        }
        if (app.keyboard[SDL_SCANCODE_W]) {     // fire
            fireBullet(wedge);
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_Q]) {     // hyperspace
            printf("Hyperspace\n");
        }
        wedge.move();
    }
    if (needle.isAlive()) {
        if (app.keyboard[SDL_SCANCODE_J]) {     // turn CCW
            needle.turn(-TURNSPEED);
            printf("J\n");
        }
        if (app.keyboard[SDL_SCANCODE_L]) {     // turn CW
            needle.turn(TURNSPEED);
            printf("L\n");
        }
        if (app.keyboard[SDL_SCANCODE_K]) {     // thrust
            needle.thrust(THRUSTFORCE);
            printf("Thrusting...\n");
        }
        if (app.keyboard[SDL_SCANCODE_I]) {     // fire
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_U]) {     // hyperspace
            printf("Hyperspace\n");
        }
        needle.move();
    }
}

static void fireBullet(Spaceship s){
	Entity *bullet;
	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));

	bullet->x = s.x;
	bullet->y = s.y;
	bullet->dx = BULLET_SPEED;
	bullet->status = 1;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (s.h / 2) - (s.h / 2);
}

static void draw() {
    wedge.draw();
    needle.draw();
}
