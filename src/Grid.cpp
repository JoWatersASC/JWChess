#include<math.h>

#include"Grid.hpp"

namespace jwchess {
//Forward Declarations
namespace Grid {
	namespace {
	struct orientation {
		bool forward	= false;
		bool backward	= false;
		bool left		= false;
		bool right		= false;
		bool horizontal = false;
		bool vertical	= false;
		bool diagonal	= false;
		bool l			= false;

		short int dist  = 3;
	};
	}

	orientation getOrientation(const space& a, const space& b);
	static bool isLegalMoveK(const move& m, const grid& g, const orientation& o);
	static bool isLegalMoveQ(const move& m, const grid& g, const orientation& o);
	static bool isLegalMoveR(const move& m, const grid& g, const orientation& o);
	static bool isLegalMoveN(const move& m, const grid& g, const orientation& o);
	static bool isLegalMoveB(const move& m, const grid& g, const orientation& o);
	static bool isLegalMoveP(const move& m, const grid& g, const orientation& o);
}

//Member function implementation
namespace Grid{
	void move::act() {
		if (curr.m_state & sState::VACANT || &curr == &next) return;

		next.m_piece = curr.m_piece;
		next.m_piece.moved = true;
		curr.m_piece = piece();

		next.m_state = sState::OCCUPIED | sState::INACTIVE;
		curr.m_state = sState::VACANT | sState::INACTIVE;
	}
	void move::undo() {
		curr = origin;
		next = destination;
	}

	grid::grid() : turn(true), inCheck(false) {
		for (int i = 0; i < 64; i++) {
			spaces[i] = space(i / 8, i % 8);

			piece& p = spaces[i].m_piece;
			if (i < 16) p.color = pCol::B;
			else p.color = pCol::W;



			if (i < 8 || i >= 56) {
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

			spaces[i].m_state |= sState::INACTIVE;
		}
	}

	std::set<int> grid::getLegalMoves(const int index) {
		int row, col;
		getRowCol(index, row, col);
		return getLegalMoves(row, col);
	}
	std::set<int> grid::getLegalMoves(const int row, const int col) {
		space& s = spaces[getSpace(row, col)];
		std::set<int> out;

		for (int i = 0; i < 64; i++) {
			space& next = spaces[i];
			move m(s, next);

			if (isLegalMoveCheck(m, *this)) out.insert(i);
		}

		legal_moves = out;
		return out;
	}
	bool grid::isInCheck() {
		pCol _turn = (turn) ? pCol::W : pCol::B;
		space* king = &spaces[0];
		int king_space = -1;

		for (int i = 0; i < 64; i++) {
			space* space = &spaces[i];
			auto space_p = space->m_piece;

			if (space_p.color == _turn && space_p.rank == pRank::K) {
				king = space;
				king_space = i;
				break;
			}
		}
		for (int i = 0; i < 64; i++) {
			space& space = spaces[i];
			if (space.m_state & sState::VACANT || space.m_piece.color == _turn) continue;
			move m(space, *king);

			turn = !turn;
			if (isLegalMove(m, *this)) {
				check_space = king_space;
				turn = !turn;
				return true;
			}
			turn = !turn;
		}

		check_space = -1;
		return false;
	}
	bool grid::isInCheckMate() {
		for (int i = 0; i < 64; i++) {
			space& s = spaces[i];
			if (s.m_state & sState::VACANT || (int)s.m_piece.color != turn) continue;
			if (getLegalMoves(i).size() > 0) return false;
		}

		return true;
	}

	bool isLegalMove(move& m, grid& g) {
		if (m.curr.m_piece.color == m.next.m_piece.color && (m.next.m_state & sState::OCCUPIED)) return false;
		if ((int)m.curr.m_piece.color != g.turn) return false;
		orientation o = getOrientation(m.curr, m.next);

		switch (m.curr.m_piece.rank) {
		case pRank::K:
			return isLegalMoveK(m, g, o);
			break;
		case pRank::Q:
			return isLegalMoveQ(m, g, o);
			break;
		case pRank::B:
			return isLegalMoveB(m, g, o);
			break;
		case pRank::N:
			return isLegalMoveN(m, g, o);
			break;
		case pRank::R:
			return isLegalMoveR(m, g, o);
			break;
		case pRank::P:
			return isLegalMoveP(m, g, o);
			break;
		default:
			break;
		}

		return false;
	}
	bool isLegalMoveCheck(move& m, grid& g) {
		if (m.curr.m_piece.color == m.next.m_piece.color && (m.next.m_state & sState::OCCUPIED)) return false;
		if ((int)m.curr.m_piece.color != g.turn) return false;
		orientation o = getOrientation(m.curr, m.next);

		{
			bool temp = true;
			m.act();
			if (g.isInCheck())
				temp = false;
			m.undo();
			if (!temp) return temp;
		}

		switch (m.curr.m_piece.rank) {
		case pRank::K:
			return isLegalMoveK(m, g, o);
			break;
		case pRank::Q:
			return isLegalMoveQ(m, g, o);
			break;
		case pRank::B:
			return isLegalMoveB(m, g, o);
			break;
		case pRank::N:
			return isLegalMoveN(m, g, o);
			break;
		case pRank::R:
			return isLegalMoveR(m, g, o);
			break;
		case pRank::P:
			return isLegalMoveP(m, g, o);
			break;
		default:
			break;
		}

		return false;
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

//Static function implementation
namespace Grid {
	orientation getOrientation(const space& a, const space& b) {

		orientation out;
		int ax, ay, bx, by;
		ax = a.col; ay = a.row;
		bx = b.col; by = b.row;

		if (a.m_state & sState::VACANT);
		else {
			piece p = a.m_piece;
			out.forward  = (p.color == pCol::B) ? ay < by : ay > by;
			out.backward = (p.color == pCol::B) ? ay > by : ay < by;
			out.left	 = (p.color == pCol::B) ? ax < bx : ax > bx;
			out.right	 = (p.color == pCol::B) ? ax > bx : ax < bx;
		}
		if (abs(bx - ax) == abs(by - ay)) out.diagonal = true;
		if (ax == bx && ay != by) out.vertical = true;
		if (ay == by && ax != bx) out.horizontal = true;
		if (ax + 2 == bx || ax - 2 == bx) {
			if (ay + 1 == by || ay - 1 == by) out.l = true;
			out.dist = 3;
			return out;
		}
		if (ay + 2 == by || ay - 2 == by) {
			if (ax + 1 == bx || ax - 1 == bx) {
				out.l = true;
				out.dist = 3;
				return out;
			}
		}

		if (out.diagonal) {
			out.dist = abs(bx - ax);
		}
		if (out.horizontal) {
			out.dist = abs(bx - ax);
		}
		if (out.vertical) {
			out.dist = abs(by - ay);
		}

		return out;
	}
	
	bool isLegalMoveK(const move& m, const grid& g, const orientation& o) {
		if (o.dist > 1) return false;
		return true;
	}
	bool isLegalMoveQ(const move& m, const grid& g, const orientation& o) {
		if (!o.diagonal && !o.horizontal && !o.vertical) return false;
		return isLegalMoveB(m, g, o) || isLegalMoveR(m, g, o);
	}
	bool isLegalMoveR(const move& m, const grid& g, const orientation& o) {
		if (!o.horizontal && !o.vertical) return false;
		int row = m.curr.row;
		int col = m.curr.col;

		int dest_row = m.destination.row;
		int dest_col = m.destination.col;

		if (o.vertical) {
			row += (row < dest_row) ? 1 : -1;
			while (row != dest_row) {
				if (g.spaces[getSpace(row, col)].m_state & sState::OCCUPIED) return false;
				if(row != dest_row) row += (row < dest_row) ? 1 : -1;
			}
		}
		else if (o.horizontal) {
			col += (col < dest_col) ? 1 : -1;
			while (col != dest_col) {
				if (g.spaces[getSpace(row, col)].m_state & sState::OCCUPIED) return false;
				if(col != dest_col) col += (col < dest_col) ? 1 : -1;
			}
		}

		return true;
	}
	bool isLegalMoveN(const move& m, const grid& g, const orientation& o) {
		if (o.l) return true;
		return false;
	}
	bool isLegalMoveB(const move& m, const grid& g, const orientation& o) {
		if (!o.diagonal) return false;
		int row = m.curr.row;
		int col = m.curr.col;

		int dest_row = m.next.row;
		int dest_col = m.next.col;

		row += (row < dest_row) ? 1 : -1;
		col += (col < dest_col) ? 1 : -1;
		while (row != dest_row && col != dest_col) {
			const space& s = g.spaces[getSpace(row, col)];
			if (s.m_state & sState::OCCUPIED)
				return false;
			if (row != dest_row && col != dest_col) {
				row += (row < dest_row) ? 1 : -1;
				col += (col < dest_col) ? 1 : -1;
			}
		}

		return true;
	}
	bool isLegalMoveP(const move& m, const grid& g, const orientation& o) {
		if (o.backward || o.horizontal || o.l || o.dist > 2) return false;
		if (o.diagonal) return m.next.m_state & sState::OCCUPIED && o.dist == 1;

		return ((o.dist == 1) || !m.curr.m_piece.moved) && !(m.next.m_state & sState::OCCUPIED);
	}
}
}