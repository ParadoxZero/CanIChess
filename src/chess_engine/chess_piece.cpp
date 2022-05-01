#include "chess_piece.h"

#include <vector>
#include <algorithm>

namespace chess_engine {

	template<class T> using ChessBoardMatrix = std::array<std::array<std::unique_ptr<T>, 8>, 8>;

	const base::Vector2Di ChessPiece::INVALID = { -1,-1 };

	std::vector<base::Vector2Di> ChessPiece::getPossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map)
	{
		if(_board != nullptr && _cachedFrom == current_position)
		{
			return _cachedMoves;
		}
		
		return generatePossibleMoves(current_position, map);
	}

	std::vector<base::Vector2Di> ChessPiece::getAllMoves(base::Vector2Di from, ChessBoardMatrix<ChessPiece>& map)
	{
		return generatePossibleMoves(from, map, false);
	}


	bool ChessPiece::isValidMove(base::Vector2Di from, base::Vector2Di to, ChessBoardMatrix<ChessPiece>& map)
	{
		if (_cachedFrom != from)
		{
			_cachedFrom = from;
			generatePossibleMoves(from, map);
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

	ChessPiece::~ChessPiece()
	{
		if (_board != nullptr && _registrationToken > 0)
		{
			_board->UnsubscribeToTurnNotification(_registrationToken);
		}
		_board = nullptr;
	}
}