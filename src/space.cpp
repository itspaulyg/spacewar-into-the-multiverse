#include "space.h"

static void logic();
static void draw();
static void doShips();
static void fireBullet(double x, double y, int h, double angle);
static void drawBullets();
static void doBullets();
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

    memset(&stage, 0, sizeof(Stage));
	  stage.bulletTail = &stage.bulletHead;

    wedge.loadSprite("./wedge.png");
    needle.loadSprite("./needle.png");
    bulletTexture = loadTexture(const_cast<char*>("bullet.png"));
}

static void logic() {
    doShips();
    doBullets();
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
            fireBullet(wedge.x, wedge.y, wedge.h, wedge.angle);
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

static void fireBullet(double x, double y, int h, double angle){
	Entity *bullet;
	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));

  stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = x;
	bullet->y = y;
  bullet->dx += (cos(angle * (PI / 180.0)) * BULLET_SPEED);
  bullet->dy += (sin(angle * (PI / 180.0)) * BULLET_SPEED);
	bullet->status = 1;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (h / 2) - (bullet->h / 2);

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
    wedge.draw();
    needle.draw();
    drawBullets();
}
