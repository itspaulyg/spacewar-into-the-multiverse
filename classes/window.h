#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Window {

	public:
		Window(const std::string &title, int width, int height);
		~Window();
		Window(const Window&);
		Window operator=(const Window&);

		void pollEvents(SDL_Event &event);
		void clear() const;

		inline bool isClosed() const { return closed;}

	private:
		bool init();

		std::string title = "Tutorial";
		int width = 1080;
		int height = 920;
		bool closed = false;

		SDL_Window *window = nullptr;

	protected:
		SDL_Renderer *renderer = nullptr;
};
