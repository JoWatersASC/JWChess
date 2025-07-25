#pragma once


#include "SDL_video.h"
namespace jwchess
{

static SDL_Window* window;

int  Init();
void Run();
int  End();

} // namespace jwchess
