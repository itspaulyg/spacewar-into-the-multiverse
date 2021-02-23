typedef struct Entity Entity;

typedef struct {
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity {
  double x, y;            // position (coordinates)
  int w, h;               // width and height of displayed texture
  double dx, dy;          // velocity vectors
  double angle;           // angle in degrees
	int health;
  bool alive;
	int status;  // whether bullet is displayed (1) or not (0)
	SDL_Texture *texture;
	Entity *next;
};

typedef struct {
	Entity bulletHead, *bulletTail;
} Stage;
