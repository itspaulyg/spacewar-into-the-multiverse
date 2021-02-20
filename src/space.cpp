#include "space.h"

static void logic();
static void draw();
static void doShips();
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

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    wedge.loadSprite("./wedge.png");
    needle.loadSprite("./needle.png");
}

static void logic() {
    doShips();
}

static void doShips() {
    if (wedge.isAlive()) {
        if (app.keyboard[SDL_SCANCODE_A]) {     // turn CCW
            wedge.turn(TURNSPEED);
            printf("A\n");
        }
        if (app.keyboard[SDL_SCANCODE_D]) {     // turn CW
            wedge.turn(-TURNSPEED);
            printf("D\n");
        }
        if (app.keyboard[SDL_SCANCODE_S]) {     // thrust
            printf("Thrusting...\n");
        }
        if (app.keyboard[SDL_SCANCODE_W]) {     // fire
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_Q]) {     // hyperspace
            printf("Hyperspace\n");
        }
    }
    if (needle.isAlive()) {
        if (app.keyboard[SDL_SCANCODE_J]) {     // turn CCW
            needle.turn(TURNSPEED);
            printf("J\n");
        }
        if (app.keyboard[SDL_SCANCODE_L]) {     // turn CW
            needle.turn(-TURNSPEED);
            printf("L\n");
        }
        if (app.keyboard[SDL_SCANCODE_K]) {     // thrust
            printf("Thrusting...\n");
        }
        if (app.keyboard[SDL_SCANCODE_I]) {     // fire
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_U]) {     // hyperspace
            printf("Hyperspace\n");
        }
    }
}

static void draw() {
    wedge.draw();
    needle.draw();
}