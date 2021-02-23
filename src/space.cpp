#include "space.h"

static void logic();
static void draw();

// Initialization
static void resetSpace();
static void initWedge();
static void initNeedle();

// Logic
static void doShips();
// static void doWedgeFire();
// static void doNeedleFire();
// static void drawBullets();
// static void bulletHitShip();
// static void shipHitShip();
// static void shipHitSun();
// static void doGravity();

//  Draw
static void drawShips();

static Entity *wedge;
static Entity *needle;
static SDL_Texture *wedge_texture;
static SDL_Texture *needle_texture;

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    wedge_texture = loadTexture((char *) "./wedge.png");
    needle_texture = loadTexture((char *) "./needle.png");

    resetSpace();
}

static void resetSpace() {
    initWedge();
    initNeedle();
}

static void initWedge() {
    wedge = (Entity *) malloc(sizeof(Entity));
    memset(wedge, 0, sizeof(Entity));

    wedge->x = WEDGE_X;
    wedge->y = WEDGE_Y;
    wedge->w = WEDGE_W;
    wedge->h = WEDGE_H;
    wedge->dx = 0;
    wedge->dy = 0;
    wedge->alive = true;
    wedge->texture = wedge_texture;
}

static void initNeedle() {
    needle = (Entity *) malloc(sizeof(Entity));
    memset(needle, 0, sizeof(Entity));

    needle->x = NEEDLE_X;
    needle->y = NEEDLE_Y;
    needle->w = NEEDLE_W;
    needle->h = NEEDLE_H;
    needle->dx = 0;
    needle->dy = 0;
    needle->alive = true;
    needle->texture = needle_texture;
}

static void logic() {
    doShips();
}

static void doShips() {
    if (wedge->alive) {
        if (app.keyboard[SDL_SCANCODE_A]) {     // turn CCW
            wedge->angle -= TURNSPEED;
            printf("A\n");
            printf("%f\n", wedge->angle);
        }
        if (app.keyboard[SDL_SCANCODE_D]) {     // turn CW
            wedge->angle += TURNSPEED;
            printf("D\n");
            printf("%f\n", wedge->angle);
        }
        if (wedge->angle > 360) {
            wedge->angle -= 360;
        }
        if (wedge->angle < -360) {
            wedge->angle += 360;
        }
        if (app.keyboard[SDL_SCANCODE_S]) {     // thrust
            wedge->dx += (cos(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
            wedge->dy += (sin(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
            printf("Thrusting...\n");
            printf("dx: %f\t dy: %f\n", wedge->dx, wedge->dy);
        }
        if (app.keyboard[SDL_SCANCODE_W]) {     // fire
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_Q]) {     // hyperspace
            printf("Hyperspace\n");
        }
    }
    if (needle->alive) {
        if (app.keyboard[SDL_SCANCODE_J]) {     // turn CCW
            needle->angle -= TURNSPEED;
            printf("J\n");
            printf("%f\n", needle->angle);
        }
        if (app.keyboard[SDL_SCANCODE_L]) {     // turn CW
            needle->angle += TURNSPEED;
            printf("L\n");
            printf("%f\n", needle->angle);
        }
        if (needle->angle > 360) {
            needle->angle -= 360;
        }
        if (needle->angle < -360) {
            needle->angle += 360;
        }
        if (app.keyboard[SDL_SCANCODE_K]) {     // thrust
            needle->dx += (cos(needle->angle * (PI / 180.0)) * THRUSTFORCE);
            needle->dy += (sin(needle->angle * (PI / 180.0)) * THRUSTFORCE);
            printf("Thrusting...\n");
            printf("dx: %f\t dy: %f\n", needle->dx, needle->dy);
        }
        if (app.keyboard[SDL_SCANCODE_I]) {     // fire
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_U]) {     // hyperspace
            printf("Hyperspace\n");
        }
    }
    wedge->x += wedge->dx;
    wedge->y += wedge->dy;
    needle->x += needle->dx;
    needle->y += needle->dy;
}

static void draw() {
    drawShips();
}

static void drawShips() {
    if (wedge->texture) {
        blit(wedge->texture, (int) round(wedge->x), (int) round(wedge->y), wedge->w, wedge->h, wedge->angle);
    } else {
        printf("Need to provide texture for ship!\n");
		exit(1);
    }
    if (needle->texture) {
        blit(needle->texture, (int) round(needle->x), (int) round(needle->y), needle->w, needle->h, needle->angle);
    } else {
        printf("Need to provide texture for ship!\n");
		exit(1);
    }
}