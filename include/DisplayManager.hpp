#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_test_font.h>
#include<iostream>

#include"Grid.hpp"

namespace jwchess {
namespace DisplayManager {
#define SCREEN_DIM 700

	static SDL_Window*   window		   = nullptr;
	static SDL_Renderer* renderer	   = nullptr;
	static SDL_Texture*	 board_texture = nullptr;
	static SDL_Texture*  pieces_sheet  = nullptr;
	
	static Grid::grid*	 s_grid		   = nullptr;
	static SDL_Rect		 board_rect;

	inline int Init(SDL_Window*);
	inline void Render(short int&);

	static SDL_Rect getTextureFromImg(SDL_Texture*&, std::string path); //creates texture from and returns dimensions of an image
}

namespace DisplayManager {
	static const short int piece_dim = 16;
	static void RenderStartScreen();
	static void RenderBoardScreen(const Grid::grid*);
	static void RenderGameOverScreen();
}
}

namespace jwchess {
namespace DisplayManager {
	int Init(SDL_Window* _window) {
		window = _window;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
		board_rect = getTextureFromImg(board_texture, "board.png");
		getTextureFromImg(pieces_sheet, "pieces.png");

		return 1;
	}

	void Render(short int& state) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xA4, 0x74, 0x49);
		SDL_RenderClear(renderer);

		switch (state) {
		case 0:
			RenderStartScreen();
			break;
		case 1:
			RenderBoardScreen(s_grid);
			break;
		case 2:
			RenderGameOverScreen();
			break;
		default:
			break;
		}
		
		SDL_RenderPresent(renderer);
	}

	SDL_Rect getTextureFromImg(SDL_Texture*& texture, std::string path) {
		int texture_width, texture_height;
		std::string texture_name = "../assets/" + path;

		SDL_Surface* tempSurface = IMG_Load(texture_name.c_str());
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);
		return { 0, 0, texture_width, texture_height };
	}
}

namespace DisplayManager {
	void RenderStartScreen() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDLTest_DrawString(renderer, SCREEN_DIM / 2 - 50, SCREEN_DIM / 4, "Chess Game");
		SDLTest_DrawString(renderer, SCREEN_DIM / 2 - 80, SCREEN_DIM/ 2, "Press any key to start");

		SDL_RenderPresent(renderer);
	}

	void RenderBoardScreen(const Grid::grid* grid) {
		int space_index = 0;
		SDL_Rect space_rect { 0, 0, space_dim, space_dim };

		for (const Grid::space& s : grid->spaces) {
			Grid::getRowCol(space_index, space_rect.y, space_rect.x);
			space_rect.x *= space_dim; space_rect.x += 75;
			space_rect.y *= space_dim; space_rect.y += 75;

			if(space_index == grid->selected_space)
				SDL_SetRenderDrawColor(renderer, 0xCB, 0xD3, 0x40, 0xFF);
			else if(grid->legal_moves.count(space_index))
				SDL_SetRenderDrawColor(renderer, 0x18, 0xCE, 0xC9, 0xFF);
			else if(space_index == grid->check_space)
				SDL_SetRenderDrawColor(renderer, 0xF8, 0x1E, 0x39, 0xFF);
			else if (space_index % 2 - (space_index / 8) % 2)
				SDL_SetRenderDrawColor(renderer, 0xA4, 0x74, 0x49, 0xFF);
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

			SDL_RenderFillRect(renderer, &space_rect);

			SDL_Rect piece_index { (int)s.m_piece.rank * piece_dim, (int)s.m_piece.color * piece_dim, piece_dim, piece_dim };
			SDL_Rect piece_disp  { space_rect.x + 4, space_rect.y + 4, space_dim - 8, space_dim - 8 };
			SDL_RenderCopy(renderer, pieces_sheet, &piece_index, &piece_disp);

			space_index++;
		}
	}

	void RenderGameOverScreen() {
		std::string result = s_grid->turn ? "Game Over Black Wins!" : "Game Over White Wins!";
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDLTest_DrawString(renderer, SCREEN_DIM / 2 - 50, SCREEN_DIM / 4, result.c_str());
		SDLTest_DrawString(renderer, SCREEN_DIM / 2 - 150, SCREEN_DIM / 2, "Press 'Enter' key to play again");

		SDL_RenderPresent(renderer);
	}
}
}
