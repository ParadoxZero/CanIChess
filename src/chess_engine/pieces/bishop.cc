#include "bishop.h"
#include "utils.h"

namespace chess_engine
{
namespace pieces 
{
std::vector<base::Vector2d> Bishop::generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly)
{
	static std::vector<base::Vector2d> directionList = {
		{1, -1},
		{-1, 1},
		{-1,-1}
	};
	_cachedMoves = getPossibleMovesInDirection(current_position, directionList, map);
	return _cachedMoves;
}

}
}
