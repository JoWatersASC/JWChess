#include "Application.hpp"

namespace jwchess {
    static Grid::grid g;

	int Init() {
		SDL_Init(SDL_INIT_EVERYTHING);
        g = Grid::grid();

        window = SDL_CreateWindow("JW Chess", 200, 60, 700, 700, 0);

        if (!Events::Init(window, &g)) exit(-1);
        if (!DisplayManager::Init(window)) exit(-1);
        DisplayManager::s_grid = &g;
        DisplayManager::window = window;

        return 0;
	}

	void Run() {
        bool running = true;

        SDL_Event e;
        short int state = 0;

        while (running) {
            while (SDL_PollEvent(&e)) {
                Events::Handle(e, state);

                if (e.type == SDL_QUIT) {
                    running = false;
                }
                if (e.type == SDL_KEYDOWN) {
                }
                if (e.type == SDL_WINDOWEVENT) {
                }
            }

            DisplayManager::Render(state);
        }
	}
}