#include "space.h"

static void logic();
static void draw();

// Initialization
static void resetSpace();
static void initWedge();
static void initNeedle();
static void initSun();

// Logic
static void doWedge();
static void doNeedle();
static void fireBullet(Entity *);
static void drawBullets();
static void doBullets();
static void doResetCheck();
static int bulletContact(Entity *);
static int shipContact();
static int sunContact();

// Boundary Logic
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
static void drawSun();
static void drawShips();

static Entity *wedge;
static Entity *needle;
static Entity *wedge_temp;
static Entity *needle_temp;
static Entity *sun;
static SDL_Texture *wedge_texture;
static SDL_Texture *needle_texture;
static SDL_Texture *bullet_texture;
static SDL_Texture *sun_texture;

bool wedge_bound = false;
bool needle_bound = false;

void initSpace() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
	stage.bulletTail = &stage.bulletHead;

    wedge_texture = loadTexture((char *) "./wedge.png");
    needle_texture = loadTexture((char *) "./needle.png");
    bullet_texture = loadTexture((char *) "./bullet.png");
    sun_texture = loadTexture((char *) "./sun.png");

    resetSpace();
}

static void resetSpace() {
    initWedge();
    initNeedle();
    initSun();
    wedge_bound = false;
    needle_bound = false;
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
    wedge->angle = WEDGE_ANGLE;
    wedge->alive = 1;
    wedge->texture = wedge_texture;
    wedge->side = SIDE_WEDGE;

    wedge_temp = (Entity *) malloc(sizeof(Entity));
    memset(wedge_temp, 0, sizeof(Entity));

    wedge_temp->x = 0;
    wedge_temp->y = 0;
    wedge_temp->w = WEDGE_W;
    wedge_temp->h = WEDGE_H;
    wedge_temp->dx = 0;
    wedge_temp->dy = 0;
    wedge_temp->alive = 1;
    wedge_temp->texture = wedge_texture;
	wedge_temp->side = SIDE_WEDGE;
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
    needle->angle = NEEDLE_ANGLE;
    needle->alive = 1;
    needle->texture = needle_texture;
    needle->side = SIDE_NEEDLE;

    needle_temp = (Entity *) malloc(sizeof(Entity));
    memset(needle_temp, 0, sizeof(Entity));

    needle_temp->x = 0;
    needle_temp->y = 0;
    needle_temp->w = NEEDLE_W;
    needle_temp->h = NEEDLE_H;
    needle_temp->dx = 0;
    needle_temp->dy = 0;
    needle_temp->alive = 1;
    needle_temp->texture = needle_texture;
    needle_temp->side = SIDE_NEEDLE;
}

static void initSun() {
    sun = (Entity *) malloc(sizeof(Entity));
    memset(sun, 0, sizeof(Entity));

    sun->x = SUN_X;
    sun->y = SUN_Y;
    sun->w = SUN_W;
    sun->h = SUN_H;
    sun->dx = 0;
    sun->dy = 0;
    sun->alive = 1;
    sun->texture = sun_texture;
    sun->side = SIDE_SUN;
}

static void logic() {
    doResetCheck();
    if(needle) doNeedle();
    if(wedge) doWedge();
    doBullets();
    shipContact();
    sunContact();
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
          if(needle_bound) {
          	needle_temp->dx += (cos(needle->angle * (PI / 180.0)) * THRUSTFORCE);
          	needle_temp->dy += (sin(needle->angle * (PI / 180.0)) * THRUSTFORCE);
		  }
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
    if (!needle_bound) setTempNeedle();
    else {
        needle_temp->x += needle_temp->dx;
        needle_temp->y += needle_temp->dy;
        checkBoundsNeedle();
    }
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
			if(wedge_bound) {
            	wedge_temp->dx += (cos(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
            	wedge_temp->dy += (sin(wedge->angle * (PI / 180.0)) * THRUSTFORCE);
			}
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
	if(!wedge_bound) setTempWedge();
	else {
		wedge_temp->x += wedge_temp->dx;
		wedge_temp->y += wedge_temp->dy;
		checkBoundsWedge();
	}
}

static void setTempWedge() {
	if(wedge->x + wedge->w >= SCREEN_WIDTH) {
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
		wedge_temp->dx = wedge->dx;
		wedge_temp->dy = wedge->dy;
	}
	if(wedge->y + wedge->h >= SCREEN_HEIGHT) {
		wedge_bound = true;
		wedge_temp->x = wedge->x;
		wedge_temp->y = 0 - wedge->h;
		wedge_temp->dx = wedge->dx;
		wedge_temp->dy = wedge->dy;
	}
	if(wedge->y <= 0) {
		wedge_bound = true;
		wedge_temp->x = wedge->x;
		wedge_temp->y = SCREEN_HEIGHT;
		wedge_temp->dx = wedge->dx;
		wedge_temp->dy = wedge->dy;
	}
}

static void setTempNeedle() {
	if(needle->x + needle->w >= SCREEN_WIDTH) {
		needle_bound = true;
		needle_temp->x = 0 - needle->w;
		needle_temp->y = needle->y;
		needle_temp->dx = needle->dx;
		needle_temp->dy = needle->dy;
	}
	if(needle->x <= 0) {
		needle_bound = true;
		needle_temp->x = SCREEN_WIDTH;
		needle_temp->y = needle->y;
		needle_temp->dx = needle->dx;
		needle_temp->dy = needle->dy;
	}
	if(needle->y + needle->h >= SCREEN_HEIGHT) {
		needle_bound = true;
		needle_temp->x = needle->x;
		needle_temp->y = 0 - needle->h;
		needle_temp->dx = needle->dx;
		needle_temp->dy = needle->dy;
	}
	if(needle->y <= 0) {
		needle_bound = true;
		needle_temp->x = needle->x;
		needle_temp->y = SCREEN_HEIGHT;
		needle_temp->dx = needle->dx;
		needle_temp->dy = needle->dy;
	}
}

static void checkBoundsWedge() {
	if(wedge->x >= SCREEN_WIDTH) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_bound = false;
	}
	if(wedge->x <= 0 - wedge->w) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_bound = false;
	}
	if(wedge->y >= SCREEN_HEIGHT) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
		wedge_bound = false;
	}
	if(wedge->y <= 0 - wedge->h) {
		wedge->x = wedge_temp->x;
		wedge->y = wedge_temp->y;
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

    e->reload = RELOAD_SPEED;  // timer value in frames for how often a bullet can be shot
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

static int shipContact() {
    if(!wedge || !needle) return 1;

    if (collision((int) needle->x, (int) needle->y, needle->w, needle->h, (int) wedge->x, (int) wedge->y, wedge->w, wedge->h)) {
        wedge->alive = 0;
        needle->alive = 0;
        return 1;
    }
    return 0;
}

static int sunContact() {
    if(!wedge || !needle) return 1;

    if (collision((int) sun->x, (int) sun->y, sun->w, sun->h, (int) wedge->x, (int) wedge->y, wedge->w, wedge->h)) {
        wedge->alive = 0;
        return 1;
    }
    if (collision((int) needle->x, (int) needle->y, needle->w, needle->h, (int) sun->x, (int) sun->y, sun->w, sun->h)) {
        needle->alive = 0;
        return 1;
    }
    return 0;
}

static void draw() {
    drawSun();
    drawShips();
    drawBullets();
}

static void drawSun() {
    if (sun->texture) {
        blit(sun->texture, (int) round(sun->x), (int) round(sun->y), sun->w, sun->h, sun->angle);
    }
}

static void drawShips() {
    if (wedge && wedge->texture) {
        blit(wedge->texture, (int) round(wedge->x), (int) round(wedge->y), wedge->w, wedge->h, wedge->angle);
		if(wedge_bound) {
        	blit(wedge->texture, (int) round(wedge_temp->x), (int) round(wedge_temp->y), wedge->w, wedge->h, wedge->angle);
		}
    }
    if (needle && needle->texture) {
        blit(needle->texture, (int) round(needle->x), (int) round(needle->y), needle->w, needle->h, needle->angle);
		if(needle_bound) {
            blit(needle->texture, (int) round(needle_temp->x), (int) round(needle_temp->y), needle->w, needle->h, needle->angle);
		}
    }
}
