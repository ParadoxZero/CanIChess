#include "pawn.h"
#include "../../base/cordinate.h"

namespace chess_engine
{
namespace pieces 
{
	static const std::vector<base::Cordinate> validMoves = {
		{0, 1},
		{0, 2}
	};

	static const std::vector<base::Cordinate> validKillMoves = {
		{1,1},
		{-1,1}
	};

	std::vector<base::Cordinate> Pawn::getPossibleMoves(base::Cordinate current_position, Tritmap& map)
	{
		std::vector<base::Cordinate> possibleMoves(validMoves.size() + validKillMoves.size());
		for (base::Cordinate i : validMoves)
		{
			base::Cordinate new_pos = current_position + i;
			if (new_pos.x < 0 || new_pos.x > 7 || new_pos.y < 0 || new_pos.y > 7)
			{
				continue;
			}

			auto tile = map[new_pos.y][new_pos.x];

		}
		return std::vector<base::Cordinate>();
	}

}
}