#include "empty.h"

namespace chess_engine
{
namespace pieces 
{
std::vector<base::Cordinate> Empty::getPossibleMoves(base::Cordinate current_position, ChessBoardMatrix<ChessPiece>& map)
{
	return std::vector<base::Cordinate>();
}

}
}
