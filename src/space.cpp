#include "space.h"

static void logic();
static void draw();

// Initialization
static void resetSpace();
static void initWedge();
static void initNeedle();

// Logic
static void doShips();
static void fireBullet(double x, double y, int h, double angle);
static void drawBullets();
static void doBullets();
static void setTempWedge();
static void setTempNeedle();
static void checkBoundsWedge();
static void checkBoundsNeedle();
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
static Entity *wedge_temp;
static Entity *needle_temp;
static SDL_Texture *wedge_texture;
static SDL_Texture *needle_texture;
static SDL_Texture *bullet_texture;

bool wedge_bound = false;
bool needle_bound = false;

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
	  stage.bulletTail = &stage.bulletHead;

    wedge_texture = loadTexture((char *) "./wedge.png");
    needle_texture = loadTexture((char *) "./needle.png");
//    bullet_texture = loadTexture(const_cast<char*>("bullet.png"));

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

    wedge_temp = (Entity *)malloc(sizeof(Entity));
    memset(wedge_temp, 0, sizeof(Entity));

    wedge_temp->x = -100;
    wedge_temp->y = -100;
    wedge_temp->w = WEDGE_W;
    wedge_temp->h = WEDGE_H;
    wedge_temp->dx = 0;
    wedge_temp->dy = 0;
    wedge_temp->alive = true;
    wedge->texture = wedge_texture;
}

static void initNeedle() {
    needle = (Entity *) malloc(sizeof(Entity));
    memset(needle, 0, sizeof(Entity));

    needle_temp = (Entity *) malloc(sizeof(Entity));
    memset(needle_temp, 0, sizeof(Entity));
	needle_temp->texture = needle_texture;

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
			if(wedge_bound) {
	            wedge_temp->dx += (cos(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
	            wedge_temp->dy += (sin(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
			}
            printf("Thrusting...\n");
            printf("dx: %f\t dy: %f\n", wedge->dx, wedge->dy);
        }
        if (app.keyboard[SDL_SCANCODE_W]) {     // fire
            fireBullet(wedge->x, wedge->y, wedge->h, wedge->angle);
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

	if(!wedge_bound) setTempWedge();
	if(!needle_bound) setTempNeedle();
	if(wedge_bound) { // make sure to set these 
		wedge_temp->x += wedge_temp->dx;
		wedge_temp->y += wedge_temp->dy;
		checkBoundsWedge();
	}
	if(needle_bound) checkBoundsNeedle();
}

static void setTempWedge() {
	if(wedge->x + wedge->w >= SCREEN_WIDTH) { // working logic; repeat for the rest
		printf("check");
		wedge_bound = true;
		wedge_temp->x = 0 - wedge->w;
		wedge_temp->y = wedge->y;
		wedge_temp->dx = wedge->dx;
		wedge_temp->dy = wedge->dy;
	}
	if(wedge->x <= 0) {
		wedge_bound = true;
		wedge_temp->x = SCREEN_WIDTH;
		wedge_temp->y = wedge->y;
	}
	if(wedge->y + wedge->h >= SCREEN_HEIGHT) {
		wedge_bound = true;
		wedge_temp->x = wedge->x;
		wedge_temp->y = 0 - wedge->h;
	}
	if(wedge->y <= 0) {
		wedge_bound = true;
		wedge_temp->x = wedge->x;
		wedge_temp->y = SCREEN_HEIGHT;
	}
}

static void setTempNeedle() {
	if(needle->x + needle->w >= SCREEN_WIDTH) {
		needle_bound = true;
		needle_temp->x = 0 - needle->w;
		needle_temp->y = needle->y;
	}
	if(needle->x <= 0) {
		needle_bound = true;
		needle_temp->x = SCREEN_WIDTH;
		needle_temp->y = needle->y;
	}
	if(needle->y + needle->h >= SCREEN_HEIGHT) {
		needle_bound = true;
		needle_temp->x = needle->x;
		needle_temp->y = 0 - needle->h;
	}
	if(needle->y <= 0) {
		needle_bound = true;
		needle_temp->x = needle->x;
		needle_temp->y = SCREEN_HEIGHT;
	}
}

static void checkBoundsWedge() {
	if(wedge->x >= SCREEN_WIDTH) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_temp->x = -100;
		wedge_temp->y = -100;
		wedge_bound = false;
	}
	if(wedge->x <= 0 - wedge->w) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_temp->x = -100;
		wedge_temp->y = -100;
		wedge_bound = false;
	}
	if(wedge->y >= SCREEN_HEIGHT) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_temp->x = -100;
		wedge_temp->y = -100;
		wedge_bound = false;
	}
	if(wedge->y <= 0 - wedge->h) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_temp->x = -100;
		wedge_temp->y = -100;
		wedge_bound = false;
	}
}

static void checkBoundsNeedle() {
	if(needle->x >= SCREEN_WIDTH) {
		needle->x = needle_temp->x;
		needle->y = needle_temp->y;
		needle_bound = false;
	}
	if(needle->x <= 0 - needle->w) {
		needle->x = needle_temp->x;
		needle->y = needle_temp->y;
		needle_bound = false;
	}
	if(needle->y >= SCREEN_HEIGHT) {
		needle->x = needle_temp->x;
		needle->y = needle_temp->y;
		needle_bound = false;
	}
	if(needle->y <= 0 - needle->h) {
		needle->x = needle_temp->x;
		needle->y = needle_temp->y;
		needle_bound = false;
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
	bullet->texture = bullet_texture;
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
    drawShips();
    drawBullets();
}

static void drawShips() {
    if (wedge->texture) {
        blit(wedge->texture, (int) round(wedge->x), (int) round(wedge->y), wedge->w, wedge->h, wedge->angle);
		if(wedge_bound) {
			printf("Drawing wedge temp...\n");
        	blit(wedge->texture, (int) round(wedge_temp->x), (int) round(wedge_temp->y), wedge->w, wedge->h, wedge->angle);
		}
    } else {
        printf("Need to provide texture for ship!\n");
		exit(1);
    }
    if (needle->texture) {
        blit(needle->texture, (int) round(needle->x), (int) round(needle->y), needle->w, needle->h, needle->angle);
		if(needle_bound) {
        	blit(needle->texture, (int) round(needle_temp->x), (int) round(needle_temp->y), needle->w, needle->h, needle->angle);
		}
    } else {
        printf("Need to provide texture for ship!\n");
		exit(1);
    }
}
