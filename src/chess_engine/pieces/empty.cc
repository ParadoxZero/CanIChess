#include "empty.h"

namespace chess_engine
{
namespace pieces 
{
std::vector<base::Cordinate> Empty::getPossibleMoves(base::Cordinate current_position, ChessBoard& board)
{
	return std::vector<base::Cordinate>();
}

}
}
