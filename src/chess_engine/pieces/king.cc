#include "king.h"
#include "utils.h"

#include<vector>

namespace chess_engine::pieces
{
	static const std::vector<base::Vector2d> validMoves = {
		{1,0},
		{1,1},
		{0,1},
		{-1,1},
		{-1,0},
		{-1,-1},
		{0,-1},
		{1,-1}
	};

	std::vector<base::Vector2d> King::generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly)
	{
		_cachedMoves.clear();
		_cachedFrom = current_position;
		auto& current_tile = map[current_position.x][current_position.y];

		if (current_tile->getType() == Empty) { return _cachedMoves; }

		for (base::Vector2d i : validMoves)
		{
			base::Vector2d new_pos = current_position + i;
			if (CheckBoardEdgeCollision(new_pos))
				continue;

			auto& new_tile = map[new_pos.x][new_pos.y];
			if (new_tile->getType() != Empty && new_tile->getColor() == current_tile->getColor())
				continue;

			_cachedMoves.push_back(new_pos);
		}

		return _cachedMoves;
	}

}
