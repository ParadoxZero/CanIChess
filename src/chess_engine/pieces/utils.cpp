#include "utils.h"
#ifndef __CHESS_ENGINE_PIECES_UTILS_
#define __CHESS_ENGINE_PIECES_UTILS_

namespace chess_engine::pieces {

    std::vector<base::Vector2Di> getPossibleMovesInDirection(base::Vector2Di current_position, std::vector<base::Vector2Di> directions, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly)
    {
        auto& current_tile = map[current_position.x][current_position.y];
        std::vector<base::Vector2Di> moveList;

        for (auto& direction : directions)
        {
            base::Vector2Di next_position = current_position + direction;
            auto exit_condition = [&next_position, &map]() {
                return !CheckBoardEdgeCollision(next_position) && map[next_position.x][next_position.y]->getType() == ChessPieceType::Empty;
            };
            while (exit_condition())
            {
                moveList.push_back(next_position);
                next_position = next_position + direction;
            } 

            if (CheckBoardEdgeCollision(next_position))
            {
                continue;
            }

            auto& last_tile = map[next_position.x][next_position.y];
            if ( last_tile->getColor() != current_tile->getColor() || ignore_friendly)
            {
                moveList.push_back(next_position);
            }
        }

        return moveList;
    }
}
#endif // !__CHESS_ENGINE_PIECES_UTILS_
