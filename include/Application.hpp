#pragma once

#include"DisplayManager.hpp"
#include"EventHandler.hpp"

namespace jwchess {
	static SDL_Window* window;

	int  Init();
	void Run();
	int  End();
}