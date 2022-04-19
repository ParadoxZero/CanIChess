#include "pawn.h"
#include "utils.h"
#include "../../base/cordinate.h"

#include <vector>

namespace chess_engine
{
namespace pieces 
{
	static const std::vector<base::Vector2d> validMoves = {
		{0, 1},
		{0, 2}
	};

	static const std::vector<base::Vector2d> validKillMoves = {
		{1,1},
		{-1,1}
	};

	static const int8_t sign_multiplier[] = { 1,-1 };
	static const int BLACK_SIGN = 1;
	static const int WHITE_SIGN = -1;

	std::vector<base::Vector2d> Pawn::getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map)
	{
		_cachedMoves.clear();
		_cachedFrom = current_position;
		auto &current_tile = map[current_position.x][current_position.y];

		if (current_tile->getType() == Empty) { return _cachedMoves; }

		int multiplier = current_tile->getColor() ==  Black ? BLACK_SIGN : WHITE_SIGN;

		for (base::Vector2d i : validMoves)
		{
			base::Vector2d new_pos = current_position + i * multiplier;
			if (CheckBoardEdgeCollision(new_pos))
				break;

			auto &tile = map[new_pos.x][new_pos.y];
			if (tile->getType() != Empty)
				break;

			_cachedMoves.push_back(new_pos);
		}

		for (base::Vector2d i : validKillMoves)
		{
			base::Vector2d new_pos = current_position + i * multiplier;
			if (CheckBoardEdgeCollision(new_pos))
				continue;

			auto &tile = map[new_pos.x][new_pos.y];
			if (tile->getType() != Empty && tile->getColor() != current_tile->getColor())
				_cachedMoves.push_back(new_pos);
		}

		return _cachedMoves;
	}

}
}