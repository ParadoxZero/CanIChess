#include "directional_move_handler.h"

namespace chess_engine {
    namespace pieces {

        std::vector<base::Vector2d> DirectionalMoveHandler::getPossibleMoves(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> moves;
            switch(direction)
            {
                case Direction::Left:  return getMovesLeft(current_position, direction, board);
                case Direction::Right:  return getMovesRight(current_position, direction, board);
                case Direction::Up:  return getMovesUp(current_position, direction, board);
                case Direction::Down:  return getMovesDown(current_position, direction, board);
                case Direction::UpLeft:  return getMovesUpLeft(current_position, direction, board);
                case Direction::DownLeft:  return getMovesDownLeft(current_position, direction, board);
                case Direction::UpRight:  return getMovesUpRight(current_position, direction, board);
                case Direction::DownRight:  return getMovesDownRight(current_position, direction, board);


            }
        }

        std::vector<base::Vector2d> DirectionalMoveHandler::getMovesLeft(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while(current_position.x > 0){
                possibleMoves.push_back(base::Vector2d(--current_position.x, current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesRight(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while(current_position.x < 8){
                possibleMoves.push_back(base::Vector2d(++current_position.x, current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesUp(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while(current_position.y > 0){
                possibleMoves.push_back(base::Vector2d(current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesDown(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while(current_position.y < 8 ){
                possibleMoves.push_back(base::Vector2d(current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesUpLeft(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while((current_position.x >0) && (current_position.y > 0)){
                possibleMoves.push_back(base::Vector2d(--current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesUpRight(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while((current_position.x < 8) && (current_position.x > 0 )){
                possibleMoves.push_back(base::Vector2d(++current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesDownLeft(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while((current_position.x > 0) && (current_position.x < 8 )){
                possibleMoves.push_back(base::Vector2d(--current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Vector2d> DirectionalMoveHandler::getMovesDownRight(base::Vector2d current_position, Direction direction, ChessBoard& board){
            std::vector<base::Vector2d> possibleMoves;
            while((current_position.x < 8) && (current_position.x < 8 )){
                possibleMoves.push_back(base::Vector2d(++current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }


    }
}