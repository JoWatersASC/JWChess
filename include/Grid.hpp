#pragma once

#include<vector>
#include<set>
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
		bool moved = false;

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

		bool operator==(const space& s) { return row == s.row && col == s.col; }
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
		bool turn; //true if white, false if black's turn
		bool inCheck; //true if turn color is in check

		short int selected_space = -1;
		short int check_space = -1;
		std::set<int> legal_moves;

		grid();

		std::set<int> getLegalMoves(const int index);
		std::set<int> getLegalMoves(const int row, const int col);
		bool isInCheck();

		space& operator[](const int index) { return spaces[index]; }
		space& operator[](const char* c)   { return this->operator[](getSpace(c)); }
	};

	bool isLegalMove(move&, grid&);
	bool isLegalMoveCheck(move&, grid&);
}
}