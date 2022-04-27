#include "empty.h"

namespace chess_engine
{
namespace pieces 
{
std::vector<base::Vector2d> Empty::generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly)
{
	return std::vector<base::Vector2d>();
}

}
}
