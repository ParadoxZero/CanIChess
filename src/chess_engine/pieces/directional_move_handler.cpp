#include "directional_move_handler.h"

namespace chess_engine {
    namespace pieces {

        std::vector<base::Cordinate> DirectionalMoveHandler::getPossibleMoves(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> moves;
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

        std::vector<base::Cordinate> DirectionalMoveHandler::getMovesLeft(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while(current_position.x > 0){
                possibleMoves.push_back(base::Cordinate(--current_position.x, current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesRight(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while(current_position.x < 8){
                possibleMoves.push_back(base::Cordinate(++current_position.x, current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesUp(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while(current_position.y > 0){
                possibleMoves.push_back(base::Cordinate(current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesDown(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while(current_position.y < 8 ){
                possibleMoves.push_back(base::Cordinate(current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesUpLeft(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while((current_position.x >0) && (current_position.y > 0)){
                possibleMoves.push_back(base::Cordinate(--current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesUpRight(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while((current_position.x < 8) && (current_position.x > 0 )){
                possibleMoves.push_back(base::Cordinate(++current_position.x, --current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesDownLeft(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while((current_position.x > 0) && (current_position.x < 8 )){
                possibleMoves.push_back(base::Cordinate(--current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }

         std::vector<base::Cordinate> DirectionalMoveHandler::getMovesDownRight(base::Cordinate current_position, Direction direction, ChessBoard& board){
            std::vector<base::Cordinate> possibleMoves;
            while((current_position.x < 8) && (current_position.x < 8 )){
                possibleMoves.push_back(base::Cordinate(++current_position.x, ++current_position.y));
            }
            return possibleMoves;
        }


    }
}