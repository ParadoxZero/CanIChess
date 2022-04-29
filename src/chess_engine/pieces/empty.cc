#include "empty.h"

namespace chess_engine
{
namespace pieces 
{
std::vector<base::Vector2Di> Empty::generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly)
{
	return std::vector<base::Vector2Di>();
}

}
}
