#include "draw.h"

void prepareScene(void) {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void) {
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);
	if (!texture) {
		printf("Couldn't load texture: %s\n", IMG_GetError());
		exit(1);
	}
	
	return texture;
}

// https://en.wikipedia.org/wiki/Bit_blit
void blit(SDL_Texture *texture, int x, int y, int w, int h, double angle) {
	SDL_Rect dest = {x, y, w, h};
	// If you want actual w/h values of image use:
	// SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (SDL_RenderCopyEx(app.renderer, texture, nullptr, &dest, angle, NULL, SDL_FLIP_NONE) < 0) {
		printf("Couldn't render texture: %s\n", SDL_GetError());
		exit(1);
	}
}
