#ifndef _CHESS_ENGINE_PIECES_UTILS_
#define _CHESS_ENGINE_PIECES_UTILS_

#include "../../base/cordinate.h"
#include "../chess_board.h"

namespace chess_engine {
namespace pieces {

	static const int8_t BOARD_TOP = 7;
	static const int8_t BOARD_BOTTON = 0;
	static const int8_t BOARD_LEFT = 0;
	static const int8_t BOARD_RIGHT = 7;

	inline bool CheckBoardEdgeCollision(base::Vector2d& new_pos)
	{
		return new_pos.x < BOARD_LEFT || new_pos.x > BOARD_RIGHT || new_pos.y < BOARD_BOTTON || new_pos.y > BOARD_TOP;
	}

	std::vector<base::Vector2d> getPossibleMovesInDirection(base::Vector2d current_position, std::vector<base::Vector2d> directions, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false);


}
}

#endif // !_CHESS_ENGINE_PIECES_UTILS_