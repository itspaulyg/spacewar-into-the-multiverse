#include "../classes/window.h"

Window::Window(const std::string &titleIn, int widthIn, int heightIn) :
	title(titleIn), width(widthIn), height(heightIn)
{
	closed = !init();
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

Window::Window(const Window& copy) {
	title = copy.title;
	width = copy.width;
	height = copy.height;
	closed = copy.closed;
	window = copy.window;
	renderer = copy.renderer;
}

bool Window::init() {
	if(SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "IMG Init failed" << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if(!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if(!renderer) {
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event &event) {
	switch(event.type) {
		case SDL_QUIT:
			closed = true;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_a:
					break;
				case SDLK_ESCAPE:
					closed = true;
					break;
				default:
					break;
			}
		default:
			break;
	}
}

void Window::clear() const {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
