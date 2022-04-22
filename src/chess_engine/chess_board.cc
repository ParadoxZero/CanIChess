#include "chess_board.h"
#include "chess_piece.h"
#include "../base/result.h"

#include <memory>
#include <vector>
#include <set>

using namespace std;
using namespace base;

#define BLACK(a) {ChessPieceFactory::createPiece(a, Black, this)}
#define WHITE(a) {ChessPieceFactory::createPiece(a, White, this)}
#define EMPTY {ChessPieceFactory::createEmpty()}

namespace chess_engine
{

    ChessBoard::ChessBoard() : 
        _turnObservers(),
        _moveHistory()
    {
        SubscribeToTurnNotification(this);

        _state = {{
            {{BLACK(Rook),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Rook)}},
            {{BLACK(Bishop), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Bishop)}},
            {{BLACK(Knight), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Knight)}},
            {{BLACK(King),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Queen)}},
            {{BLACK(Queen),  BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(King)}},
            {{BLACK(Knight), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Knight)}},
            {{BLACK(Bishop), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Bishop)}},
            {{BLACK(Rook),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Rook)}},
        }};
    }

    PieceColor ChessBoard::getCurrentColor()
    {
        /* White always starts first, number of moves played so far
            will always be even when it's White's turn. 
            e.g.   turn number  history size
                            1   0
                            3   2
                            5   4                                       
            So no need to track turns seperately   */
        return _moveHistory.size() % 2 == 0 ? White : Black;
    }

    ChessBoardMatrix<ChessPiece> ChessBoard::getState()
    { 
        ChessBoardMatrix<ChessPiece> copyState;
        for (int i = 0; i < copyState.size(); ++i)
        {
            for (int j = 0; j < copyState[i].size(); ++j)
            {
                copyState[i][j] = _state[i][j]->Clone();
            }
        }
        return copyState;
    }

    Result ChessBoard::playMove(base::Vector2d from, base::Vector2d to)
    {
        Result result;
        auto subject = _state[from.x][from.y].get();
        if (subject->getColor() != getCurrentColor())
        {
            return Result::InvalidArgument;
        }

        if (!subject->isValidMove(from, to, _state))
        {
            return Result::InvalidArgument;
        }

        if (_promotionCandidate)
        {
            return Result::PendingPromotion;
        }

        _state[to.x][to.y] = move(_state[from.x][from.y]);
        _state[from.x][from.y] = ChessPieceFactory::createEmpty();
        _moveHistory.push_back({ from, to });
        result = Result::Success;

        if (Check(to))
        {
            result = Result::Check;

            if (Checkmate())
            {
                result = Result::Checkmate;
            }
        }

        if (Promote(to))
        {
            _promotionCandidate.reset(new Vector2d{ to.x, to.y });
            result = Result::Promote;
        }

        NotifyNextTurn();

        return result;
    }

    std::vector<base::Vector2d> ChessBoard::getPossibleMoves(base::Vector2d from)
    {
        return _state[from.x][from.y]->getPossibleMoves(from, _state);
    }

    ObserverRegistrationToken ChessBoard::SubscribeToTurnNotification(IObserver *observer)
    {
        size_t index = _turnObservers.size();
        _turnObservers.push_back(observer);
        return index;
    }

    void ChessBoard::UnsubscribeToTurnNotification(ObserverRegistrationToken token)
    {
        if(token > _turnObservers.size()) return;
        auto oberverToRemove = _turnObservers.begin() + token;
        _turnObservers.erase(oberverToRemove);
    }

    bool ChessBoard::NotifyNextTurn()
    {
        for (auto observer : _turnObservers)
        {
            observer->NextTurnEvent();
        }
        return true;
    }

    bool ChessBoard::Check(base::Vector2d from)
    {
        auto current_color = _state[from.x][from.y]->getColor();
        auto possibleMOves = _state[from.x][from.y]->getPossibleMoves(from, _state);
        for (auto& move : possibleMOves)
        {
            auto piece = _state[move.x][move.y].get();
            if (current_color != piece->getColor() && piece->getType() == ChessPieceType::King)
            {
                return true;
            }
        }
        
        return false;
    }

    bool ChessBoard::Checkmate()
    {
        auto current_color = getCurrentColor();
        ChessPiece* enemy_king = nullptr;
        vector<base::Vector2d> enemy_king_moves;
        bool map[8][8] = { 0 };
        for (int8_t i = 0; i < _state.size(); ++i)
        {
            for (int8_t j = 0; j < _state[i].size(); ++j)
            {
                if (_state[i][j]->getColor() == current_color)
                {
                    vector<base::Vector2d> moveList = _state[i][j]->getAllMoves({i,j});
                    for (auto& move : moveList)
                    {
                        map[move.x][move.y] = true;
                    }
                }
                else if (_state[i][j]->getType() == ChessPieceType::King )
                {
                    enemy_king_moves = _state[i][j]->getPossibleMoves({i,j}, _state);
                }
            }
        }

        for (auto& move : enemy_king_moves)
        {
            if (!_state[move.x][move.y])
            {
                return false;
            }
        }
        return true;
    }

    bool ChessBoard::Promote(base::Vector2d from)
    {
        auto piece = _state[from.x][from.y].get();

        static const int8_t WHITE_EDGE_Y = 0;
        static const int8_t BLACK_EDGE_Y = 7;

        if (piece->getType() == ChessPieceType::Pawn)
        {
            if (piece->getColor() == PieceColor::White)
            {
                return from.y == WHITE_EDGE_Y;
            }
            else
            {
                return from.y == BLACK_EDGE_Y;
            }
        }
        return false;
    }

    bool ChessBoard::NextTurnEvent() {
        return true;
    }

    bool ChessBoard::PromotePawn(ChessPieceType to)
    {
        if (_promotionCandidate)
        {
            auto color = _state[_promotionCandidate->x][_promotionCandidate->y]->getColor();
            _state[_promotionCandidate->x][_promotionCandidate->y] = ChessPieceFactory::createPiece(to, color, this);
            _promotionCandidate.reset(nullptr);
        }
        return false;
    }
};