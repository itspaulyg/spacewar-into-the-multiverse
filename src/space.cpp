#include "space.h"

static void logic();
static void draw();

// Initialization
static void resetSpace();
static void initWedge();
static void initNeedle();

// Logic
static void doShips();
static void fireBullet(Entity*);
static void drawBullets();
static void doBullets();
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
static SDL_Texture *bullet_texture;

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
	  stage.bulletTail = &stage.bulletHead;

    wedge_texture = loadTexture((char *) "./wedge.png");
    needle_texture = loadTexture((char *) "./needle.png");
    bullet_texture = loadTexture(const_cast<char*>("bullet.png"));

    resetSpace();
}

static void resetSpace() {
    initWedge();
    initNeedle();
}

static void initWedge() {
    wedge = (Entity *)malloc(sizeof(Entity));
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
    doBullets();
}

static void doShips() {
    if (wedge->alive) {
        if (wedge->reload > 0){ // acts as a timer to prevent bullet spam
          wedge->reload--;
        }

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
        if (app.keyboard[SDL_SCANCODE_W] && wedge->reload == 0) {     // fire
            fireBullet(wedge);
            printf("Firing\n");
        }
        if (app.keyboard[SDL_SCANCODE_Q]) {     // hyperspace
            printf("Hyperspace\n");
        }
    }
    if (needle->alive) {
        if (needle->reload > 0){ // acts as a timer to prevent bullet spam
          needle->reload--;
        }
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
        if (app.keyboard[SDL_SCANCODE_I] && needle->reload == 0) {     // fire
            fireBullet(needle);
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

    if (app.keyboard[SDL_SCANCODE_R]) {     // Reset
        resetSpace();
        printf("Reset\n");
    }
}

static void fireBullet(Entity* e){
	Entity *bullet;
	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));

  stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;
  bullet->dx += (cos(e->angle * (PI / 180.0)) * BULLET_SPEED);
  bullet->dy += (sin(e->angle * (PI / 180.0)) * BULLET_SPEED);
	bullet->status = 1;
	bullet->texture = bullet_texture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullet->y += (e->h / 2) - (bullet->h / 2);

  e->reload = 500;  // timer value in frames for how often a bullet can be shot
}

static void drawBullets(){
	Entity *b;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next){
		blit(b->texture, (int)b->x, (int)b->y);
	}
}

static void doBullets(){
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next){
		b->x += b->dx;
		b->y += b->dy;

		if (0 > b->x || b->x > SCREEN_WIDTH || 0 > b->y || b->y > SCREEN_HEIGHT){
			if (b == stage.bulletTail){
				stage.bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}

static void draw() {
    drawShips();
    drawBullets();
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
