#include "chess_board.h"
#include "chess_piece.h"
#include "../base/result.h"

#include <memory>

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
        auto subject = _state[from.x][from.y].get();
        if (subject->getColor() != getCurrentColor())
        {
            return Result::InvalidArgument;
        }

        if (!subject->isValidMove(from, to, _state))
        {
            return Result::InvalidArgument;
        }

        _state[to.x][to.y] = move(_state[from.x][from.y]);
        _state[from.x][from.y] = ChessPieceFactory::createEmpty();
        _moveHistory.push_back({ from, to });

        NotifyNextTurn();

        return Result::Success;
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

    bool ChessBoard::NextTurnEvent() {
        return true;
    }
};