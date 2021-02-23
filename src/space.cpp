#include "space.h"

static void logic();
static void draw();

// Initialization
static void resetSpace();
static void initWedge();
static void initNeedle();

// Logic
static void doNeedle();
static void doWedge();
static void fireBullet(Entity*);
static void drawBullets();
static void doBullets();
static void doResetCheck();
static int bulletContact(Entity*);
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
    wedge->alive = 1;
    wedge->texture = wedge_texture;
    wedge->side = SIDE_WEDGE;
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
    needle->alive = 1;
    needle->texture = needle_texture;
    needle->side = SIDE_NEEDLE;
}

static void logic() {
    doResetCheck();
    if(needle) doNeedle();
    if(wedge) doWedge();
    doBullets();
}

static void doResetCheck(){
  if (app.keyboard[SDL_SCANCODE_R]) {
      resetSpace();
      printf("Reset\n");
  }
}

static void doNeedle(){
  if(!needle) return;
  if (!needle->alive){          // if needle died
    if(needle != NULL){
      printf("Deleting needle\n");
      free(needle);
      needle = NULL;
      return;
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
  needle->x += needle->dx;
  needle->y += needle->dy;
}


static void doWedge() {
    if(!wedge) return;  // if wedge died
    if (!wedge->alive){
      if(wedge != NULL){
        printf("Deleting wedge\n");
        free(wedge);
        wedge = NULL;
        return;
      }
    }
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
    wedge->x += wedge->dx;
    wedge->y += wedge->dy;
}

static void fireBullet(Entity* e){
  if(!e) return;
	Entity *bullet;
	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));

  stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;
  bullet->dx += (cos(e->angle * (PI / 180.0)) * BULLET_SPEED);
  bullet->dy += (sin(e->angle * (PI / 180.0)) * BULLET_SPEED);
	bullet->alive = 1;
  bullet->side = e->side; // belongs to team of whoever shot it
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

		if (bulletContact(b) || 0 > b->x || b->x > SCREEN_WIDTH || 0 > b->y || b->y > SCREEN_HEIGHT){
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

static int bulletContact(Entity *b){
  if(!wedge || !needle) return 1;

  if (wedge->side != b->side && collision((int)b->x, (int)b->y, b->w, b->h, (int)wedge->x, (int)wedge->y, wedge->w, wedge->h)){
    b->alive = 0;
    wedge->alive = 0;

    return 1;
  }

  if (needle->side != b->side && collision((int)b->x, (int)b->y, b->w, b->h, (int)needle->x, (int)needle->y, needle->w, needle->h)){
    b->alive = 0;
    needle->alive = 0;

    return 1;
  }

	return 0;
}

static void draw() {
    drawShips();
    drawBullets();
}

static void drawShips() {
    if (wedge && wedge->texture) {
        blit(wedge->texture, (int) round(wedge->x), (int) round(wedge->y), wedge->w, wedge->h, wedge->angle);
    }
    if (needle && needle->texture) {
        blit(needle->texture, (int) round(needle->x), (int) round(needle->y), needle->w, needle->h, needle->angle);
    }
}
