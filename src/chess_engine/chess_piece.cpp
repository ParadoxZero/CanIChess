#include "chess_piece.h"

#include <vector>
#include <algorithm>

namespace chess_engine {

	const base::Cordinate ChessPiece::INVALID = { -1,-1 };

	bool ChessPiece::isValidMove(base::Cordinate from, base::Cordinate to, Tritmap& map)
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

	bool ChessPiece::NextTurnEvent()
	{
		_cachedMoves.clear();
		_cachedFrom = INVALID;
		return true;
	}
}