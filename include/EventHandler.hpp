#pragma once

#include<SDL2/SDL.h>
#include"Grid.hpp"

namespace jwchess {
namespace Events{
	static SDL_Window* window = nullptr;
	static Grid::grid* s_grid = nullptr;

	inline int Init(SDL_Window*, Grid::grid*);
	inline void Handle(const SDL_Event&);

	static int getIndexFromCoords(int& _x, int& _y);
	static std::stack<Grid::move> movestk;
}


namespace Events {
	int Init(SDL_Window* _window, Grid::grid* _grid) {
		window = _window;
		s_grid = _grid;

		if (!window || !s_grid) return 0;
		return 1;
	}

	void Handle(const SDL_Event& e) {
		//350 + 8 * space_dim;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x < 75 || x > 75 + 8 * space_dim || y < 75 || y > 75 + 8 * space_dim) return;
			
			int index = getIndexFromCoords(x, y);

			if (!(s_grid->selected_space + 1)) {
				s_grid->selected_space = index;
				s_grid->operator[](index).m_state -= Grid::sState::INACTIVE;
				s_grid->operator[](index).m_state |= Grid::sState::SELECTED;
			}
			else {
				Grid::move m((*s_grid)[s_grid->selected_space], (*s_grid)[index]);

				if(Grid::isLegalMove(m, *s_grid)) {
					m.act();
					(*s_grid).turn = !(*s_grid).turn;
					movestk.push(m);
				}

				s_grid->selected_space = -1;
			}
		}

		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_BACKSPACE && !movestk.empty()) {
				movestk.top().undo();
				movestk.pop();
			}
		}
	}

	int getIndexFromCoords(int& _x, int& _y) {
		if (_x < 75 || _x > 75 + 8 * space_dim || _y < 75 || _y > 75 + 8 * space_dim) return -1;

		_x -= 75;  _x /= space_dim;
		_y -= 75;  _y /= space_dim;

		return Grid::getSpace(_y, _x);
	}
}
}