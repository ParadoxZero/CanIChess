#include "knight.h"
#include "utils.h"

namespace chess_engine::pieces
{
	static const std::vector<base::Cordinate> validMoves = {
		{1, 2},
		{-1, 2},
		{-1, -2},
		{1, -2},
		{2, 1},
		{-2, 1},
		{-2, -1},
		{2, -1}
	};

	std::vector<base::Cordinate> Knight::getPossibleMoves(base::Cordinate current_position, Tritmap& map)
	{
		_cachedMoves.clear();
		_cachedFrom = current_position;
		auto current_color = map[current_position.x][current_position.y];

		if (current_color == TRITMAP_EMPTY) { return _cachedMoves; }

		for (base::Cordinate i : validMoves)
		{
			base::Cordinate new_pos = current_position + i;
			if (CheckBoardEdgeCollision(new_pos))
				continue;

			auto new_tile = map[new_pos.x][new_pos.y];
			if (new_tile == current_color)
				continue;

			_cachedMoves.push_back(new_pos);
		}

		return _cachedMoves;
	}

}
