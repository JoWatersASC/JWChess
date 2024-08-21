#pragma once

#include<vector>
#include<stack>

namespace jwchess {
	const short int space_dim = 70;

namespace Grid{
	static enum class pCol  { B, W, X };
	static enum class pRank { K, Q, B, N, R, P, X };
	static enum sState {
		DEFAULT,
		INACTIVE  = 1 << 0,
		SELECTED  = 1 << 1,
		MOVEABLE  = 1 << 2,
		VACANT	  = 1 << 3,
		OCCUPIED  = 1 << 4
	};

	struct piece {
		pCol color;
		pRank rank;

		piece() : color(pCol::X), rank(pRank::X) {}
		piece(pCol _color, pRank _rank) : color(_color), rank(_rank){}
	};

	struct space {
		short int row, col;
		short int m_state;
		piece m_piece;

		space() : row(0), col(0), m_state(INACTIVE) {}
		space(int _row, int _col) : row(_row), col(_col), m_state(INACTIVE){}
		space(int _row, int _col, piece _p) : row(_row), col(_col), m_piece(_p), m_state(INACTIVE) {}
	};

	struct move {
		space &curr, &next;
		space origin, destination;

		move(space& _curr, space& _next) : curr(_curr), next(_next), origin(_curr), destination(_next) {}
		void act();
		void undo();

	private:
		move();
	};

	int getSpace(int _row, int _col);
	int getSpace(const char* c);
	void getRowCol(int space_index, int& _row, int& _col);
	void getRowCol(const char* c, int& _row, int& _col);

	struct grid {
		space spaces[64];
		pCol turn;

		short int selected_space = -1;
		std::stack<move> moves;
		std::vector<space> legal_moves;

		grid();

		std::vector<space> getLegalMoves(const int);
		space& operator[](const int index) { return spaces[index]; }
		space& operator[](const char* c)   { return this->operator[](getSpace(c)); }
	};

}
}