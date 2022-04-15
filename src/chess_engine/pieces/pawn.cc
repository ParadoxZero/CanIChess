#include "pawn.h"
#include "utils.h"
#include "../../base/cordinate.h"

#include <vector>
#include <algorithm>

namespace chess_engine
{
namespace pieces 
{

	const base::Cordinate Pawn::INVALID = { -1,-1 };

	static const std::vector<base::Cordinate> validMoves = {
		{0, 1},
		{0, 2}
	};

	static const std::vector<base::Cordinate> validKillMoves = {
		{1,1},
		{-1,1}
	};

	static const int8_t sign_multiplier[] = { 1,-1 };
	static const int BLACK_SIGN = 0;
	static const int WHITE_SIGN = 1;

	std::vector<base::Cordinate> Pawn::getPossibleMoves(base::Cordinate current_position, Tritmap& map)
	{
		_cachedMoves.clear();
		_cachedFrom = current_position;
		auto current_color = map[current_position.x][current_position.y];
		int multiplier = sign_multiplier[current_color == TRITMAP_BLACK ? BLACK_SIGN : WHITE_SIGN];

		if (current_color == TRITMAP_EMPTY) { return _cachedMoves; }

		for (base::Cordinate i : validMoves)
		{
			base::Cordinate new_pos = current_position + i * multiplier;
			if (CheckBoardEdgeCollision(new_pos))
				break;

			auto tile = map[new_pos.x][new_pos.y];
			if (tile != TRITMAP_EMPTY)
				break;

			_cachedMoves.push_back(new_pos);
		}

		for (base::Cordinate i : validKillMoves)
		{
			base::Cordinate new_pos = current_position + i * multiplier;
			if (CheckBoardEdgeCollision(new_pos))
				continue;

			auto tile = map[new_pos.x][new_pos.y];
			if (tile != TRITMAP_EMPTY && tile != current_color)
				_cachedMoves.push_back(new_pos);
		}

		return _cachedMoves;
	}

	bool Pawn::isValidMove(base::Cordinate from, base::Cordinate to, Tritmap& map)
	{
		if (_cachedFrom != from)
		{
			_cachedFrom = from;
			getPossibleMoves(from, map);
			return isValidMove(from, to, map);
		}

		auto found_ittr = std::find(_cachedMoves.begin(), _cachedMoves.end(), to);
		return found_ittr != _cachedMoves.end();
	}

	bool Pawn::NextTurnEvent()
	{
		_cachedMoves.clear();
		_cachedFrom = INVALID;
		return true;
	}

}
}