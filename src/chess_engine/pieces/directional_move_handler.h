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
            std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesLeft(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesRight(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesUp(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesDown(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesUpLeft(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesDownLeft(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesUpRight(base::Cordinate current_position, Direction direction, ChessBoard& board);
            std::vector<base::Cordinate> getMovesDownRight(base::Cordinate current_position, Direction direction, ChessBoard& board);

        };
    }
}