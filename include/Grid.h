#pragma once

#include<unordered_set>

namespace jwchess {
namespace Grid{
	static enum class pCol  { B, W, X };
	static enum class pRank { K, Q, B, N, R, P, X };
	static enum state {
		INACTIVE  = 0,
		SELECTED  = 1 << 0,
		MOVEABLE  = 1 << 1,
		VACANT	  = 1 << 2,
		OCCUPIED  = 1 << 3
	};

	struct piece {
		pCol color;
		pRank rank;

		piece() : color(pCol::X), rank(pRank::X) {}
		piece(pCol _color, pRank _rank) : color(_color), rank(_rank){}
	};

	struct space {
		short int row, col;
		state m_state;
		piece m_piece;

		space() : row(0), col(0), m_state(INACTIVE) {}
		space(int _row, int _col) : row(_row), col(_col), m_state(INACTIVE){}
		space(int _row, int _col, piece _p) : row(_row), col(_col), m_piece(_p), m_state(INACTIVE) {}
	};

	struct move {
		const space &prev, &next;

		move(space& _prev, space& _next) : prev(_prev), next(_next){}
		void act();
		void undo();

	private:
		move();
	};

	struct grid {
		space spaces[64];
		short int selected_space = -1;
		std::vector<space> legal_moves;

		grid();

		std::vector<space> getLegalMoves(const int);
	};

	int getSpace(int _row, int _col);
	void getRowCol(int space_index, int& _row, int& _col);
}
}