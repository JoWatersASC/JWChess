#include"Grid.h"

namespace jwchess {
namespace Grid{
	void move::act() {
		if (curr.m_state & sState::VACANT/* || curr.m_state & sState::INACTIVE*/) return;

		next.m_piece = curr.m_piece;
		curr.m_piece = piece();

		next.m_state = sState::OCCUPIED | sState::INACTIVE;
		curr.m_state = sState::VACANT   | sState::INACTIVE;
	}
	void move::undo() {
		curr = origin;
		next = destination;
	}

	grid::grid() : turn(pCol::W) {
		for (int i = 0; i < 64; i++) {
			piece p;

			if (i < 8 || i >= 56 ) {
				if (i % 8 == 0 || i % 8 == 7) p.rank = pRank::R;
				else if (i % 8 == 1 || i % 8 == 6) p.rank = pRank::N;
				else if (i % 8 == 2 || i % 8 == 5) p.rank = pRank::B;
				else if (i % 8 == 3) p.rank = pRank::K;
				else if (i % 8 == 4) p.rank = pRank::Q;
				spaces[i].m_state |= sState::OCCUPIED;
			}
			else if (i < 16 || i >= 48) {
				p.rank = pRank::P;
				spaces[i].m_state |= sState::OCCUPIED;
			}
			else {
				spaces[i].m_state |= sState::VACANT;
			}

			if (i < 16) p.color = pCol::B;
			else p.color = pCol::W;

			spaces[i] = space(i / 8, i % 8, p);
			spaces[i].m_state |= sState::INACTIVE;
		}
	}

	std::vector<space> grid::getLegalMoves(const int space_index) {
		return {};
	}

	int getSpace(int _row, int _col) {
		return _row * 8 + _col;
	}
	int getSpace(const char* c) {
		int row, col;
		getRowCol(c, row, col);
		return getSpace(row, col);
	}
	void getRowCol(int space_index, int& _row, int& _col) {
		if (space_index > 63 || space_index < 0) return;

		_row = space_index / 8;
		_col = space_index % 8;
	}
	void getRowCol(const char* c, int& _row, int& _col) {
		int index = 0;

		while (c) {
			switch (index) {
			case 0:
				if (*c < 'a' || *c > 'h') return;
				_col = *c - 'a';
				break;
			case 1:
				if (*c < '1' || *c > '8') return;
				_row = *c - '1';
				break;
			default:
				return;
			}

			index++;
			c++;
		}
	}
}
}