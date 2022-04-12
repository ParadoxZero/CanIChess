#include "pawn.h"
#include "utils.h"
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
		std::vector<base::Cordinate> possibleMoves;
		
		auto current_color = map[current_position.x][current_position.y];

		if (current_color == TRITMAP_EMPTY) { return possibleMoves; }

		for (base::Cordinate i : validMoves)
		{
			base::Cordinate new_pos = current_position + i;
			if (CheckBoardEdgeCollision(new_pos))
				break;

			auto tile = map[new_pos.x][new_pos.y];
			if (tile != TRITMAP_EMPTY)
				break;

			possibleMoves.push_back(new_pos);
		}

		for (base::Cordinate i : validKillMoves)
		{
			base::Cordinate new_pos = current_position + i;
			if (CheckBoardEdgeCollision(new_pos))
				continue;

			auto tile = map[new_pos.x][new_pos.y];
			if (tile != TRITMAP_EMPTY && tile != current_color)
				possibleMoves.push_back(new_pos);
		}

		return possibleMoves;
	}

}
}