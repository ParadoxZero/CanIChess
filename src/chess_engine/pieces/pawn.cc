#include "pawn.h"
#include "../../base/cordinate.h"

namespace chess_engine
{
namespace pieces 
{
	static const std::vector<base::Cordinate> validMovies = {
		{0, 1},
		{0, 2}
	};

	static const std::vector<base::Cordinate> validKillMove = {
		{1,1},
		{-1,1}
	};

	std::vector<base::Cordinate> Pawn::getPossibleMoves(base::Cordinate current_position, ChessBoard& board)
	{
		return std::vector<base::Cordinate>();
	}

}
}
