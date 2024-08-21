#include "Application.hpp"

namespace jwchess {
    static Grid::grid g;

	int Init() {
		SDL_Init(SDL_INIT_EVERYTHING);

        window = SDL_CreateWindow("JW Chess", 200, 60, 1280, 600, SDL_WINDOW_RESIZABLE);
        DisplayManager::window = window;

        if (!DisplayManager::Init()) exit(-1);
        DisplayManager::s_grid = &g;

        return 0;
	}

	void Run() {
        bool running = true;

        SDL_Event e;
        while (running) {
            while (SDL_PollEvent(&e)) {

                if (e.type == SDL_QUIT) {
                    running = false;
                }
                if (e.type == SDL_KEYDOWN) {
                }
                if (e.type == SDL_WINDOWEVENT) {
                }
            }

            DisplayManager::Render();
        }
	}
}