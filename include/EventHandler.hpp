#pragma once

#include<SDL2/SDL.h>
#include"Grid.hpp"
#include"DisplayManager.hpp"

namespace jwchess {
//Forward Declarations
namespace Events{
	static SDL_Window* window = nullptr;
	static Grid::grid* s_grid = nullptr;

	inline int Init(SDL_Window*, Grid::grid*);
	inline void Handle(const SDL_Event&, short int&);
	
	static void handleBoardClick(int mouse_x, int mouse_y, short int& state);
	static void handleBoardUndo();
	static int getIndexFromCoords(int& _x, int& _y);
	static std::stack<Grid::move> movestk;
}

//Implementations
namespace Events {
	int Init(SDL_Window* _window, Grid::grid* _grid) {
		window = _window;
		s_grid = _grid;

		if (!window || !s_grid) return 0;
		return 1;
	}

	void Handle(const SDL_Event& e, short int& state) {
		if (e.type == SDL_MOUSEBUTTONDOWN && state == 1) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x < 75 || x > 75 + 8 * space_dim || y < 75 || y > 75 + 8 * space_dim) return;

			handleBoardClick(x, y, state);
		}

		if (e.type == SDL_KEYDOWN) {
			switch(state) {
			case 0:
				state = 1;
				break;
			case 1:
				if (e.key.keysym.sym == SDLK_BACKSPACE && !movestk.empty())
					handleBoardUndo();
				break;
			case 2:
				if (e.key.keysym.sym == SDLK_RETURN) state = 1;
				break;
			default:
				break;
			}
			
		}
	}

	void handleBoardClick(int mouse_x, int mouse_y, short int& state) {
		int index = getIndexFromCoords(mouse_x, mouse_y);

		if (!(s_grid->selected_space + 1)) {
			s_grid->selected_space = index;
			s_grid->getLegalMoves(index);
			
			s_grid->operator[](index).m_state -= Grid::sState::INACTIVE;
			s_grid->operator[](index).m_state |= Grid::sState::SELECTED;
		}
		else {
			Grid::move m((*s_grid)[s_grid->selected_space], (*s_grid)[index]);

			if (Grid::isLegalMoveCheck(m, *s_grid)) {
				m.act();
				movestk.push(m);
				s_grid->turn = !s_grid->turn;
			}

			if (s_grid->isInCheck()) {
				if (s_grid->isInCheckMate()) state = 2;
				else s_grid->isInCheck();
			}

			s_grid->selected_space = -1;
			s_grid->legal_moves.clear();
		}
	}

	void handleBoardUndo() {
		movestk.top().undo();
		movestk.pop();

		s_grid->turn = !s_grid->turn;
		s_grid->isInCheck();
		s_grid->selected_space = -1;
		s_grid->legal_moves.clear();
	}
	int getIndexFromCoords(int& _x, int& _y) {
		if (_x < 75 || _x > 75 + 8 * space_dim || _y < 75 || _y > 75 + 8 * space_dim) return -1;

		_x -= 75;  _x /= space_dim;
		_y -= 75;  _y /= space_dim;

		return Grid::getSpace(_y, _x);
	}
}
}