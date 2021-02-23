#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int w, int h, double angle);
extern void blit(SDL_Texture *texture, int x, int y);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Stage stage;
