#include"Grid.h"

namespace jwchess {
namespace Grid{
	grid::grid() {
		for (int i = 0; i < 64; i++) {
			piece p;

			if (i < 8 || i >= 56 ) {
				if (i % 8 == 0 || i % 8 == 7) p.rank = pRank::R;
				else if (i % 8 == 1 || i % 8 == 6) p.rank = pRank::N;
				else if (i % 8 == 2 || i % 8 == 5) p.rank = pRank::B;
				else if (i % 8 == 3) p.rank = pRank::K;
				else if (i % 8 == 4) p.rank = pRank::Q;
			}
			else if (i < 16 || i >= 48) {
				p.rank = pRank::P;
			}

			if (i < 16) p.color = pCol::B;
			else p.color = pCol::W;

			spaces[i] = space(i / 8, i % 8, p);
		}
	}

	std::vector<space> grid::getLegalMoves(const int space_index) {
		return {};
	}

	int getSpace(int _row, int _col) {
		return _row * 8 + _col;
	}
	void getRowCol(int space_index, int& _row, int& _col) {
		if (space_index > 63 || space_index < 0) return;

		_row = space_index / 8;
		_col = space_index % 8;
	}
}
}