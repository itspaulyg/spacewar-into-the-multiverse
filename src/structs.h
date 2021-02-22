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

typedef struct {
	double x;
	double y;
  double dx;
  double dy;
  int w;
  int h;
	int status;
	SDL_Texture *texture;
} Entity;
