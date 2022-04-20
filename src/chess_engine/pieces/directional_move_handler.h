#pragma once

#include <vector>
#include "../../base/cordinate.h"
#include "../../chess_engine/chess_board.h"

namespace chess_engine {
    namespace pieces 
    {
        class DirectionalMoveHandler
        {
            enum Direction 
            {
                Left,
                Right,
                Up,
                Down,
                UpLeft,
                DownLeft,
                UpRight,
                DownRight
            };

            friend class DirectionalMoveHandlerTests;

        public:
            std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesLeft(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesRight(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesUp(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesDown(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesUpLeft(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesDownLeft(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesUpRight(base::Vector2d current_position, Direction direction, ChessBoard& board);
            std::vector<base::Vector2d> getMovesDownRight(base::Vector2d current_position, Direction direction, ChessBoard& board);

        };
    }
}