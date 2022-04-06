#include "chess_board.h"
#include "chess_piece.h"

#include <memory>

using namespace std;

#define BLACK(a) ChessPieceFactory::createPiece(a, Black)
#define WHITE(a) ChessPieceFactory::createPiece(a, White)
#define EMPTY ChessPieceFactory::createPiece(Empty, White)

namespace chess_engine
{

    ChessBoard::ChessBoard() : 
        _state {
            {BLACK(Rook), BLACK(Bishop), BLACK(Knight), BLACK(Queen), BLACK(King), BLACK(Knight), BLACK(Bishop), BLACK(Rook)},
            {BLACK(Pawn), BLACK(Pawn),   BLACK(Pawn),   BLACK(Pawn),  BLACK(Pawn), BLACK(Pawn),   BLACK(Pawn),   BLACK(Pawn)},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {WHITE(Pawn), WHITE(Pawn),   WHITE(Pawn),   WHITE(Pawn),  WHITE(Pawn), WHITE(Pawn),   WHITE(Pawn),   WHITE(Pawn)},
            {WHITE(Rook), WHITE(Bishop), WHITE(Knight), WHITE(Queen), WHITE(King), WHITE(Knight), WHITE(Bishop), WHITE(Rook)},
        }
    {
        SubscribeToTurnNotification(this);
    }
    void ChessBoard::getColormap(PieceColor map[][8])
    {
    }
    PieceColor ChessBoard::getCurrentColor()
    {
        return PieceColor();
    }
    void ChessBoard::playMove(base::Cordinate from, base::Cordinate to)
    {
    }
    std::vector<base::Cordinate> ChessBoard::getPossibleMoves(base::Cordinate from)
    {
        return std::vector<base::Cordinate>();
    }
    ChessBoard::ObserverRegistrationToken ChessBoard::SubscribeToTurnNotification(const IObserver *observer)
    {
        int index = _turnObservers.size();
        _turnObservers.push_back(observer);
        return index;
    }
    void ChessBoard::UnsubscribeToTurnNotification(ObserverRegistrationToken token)
    {
        auto oberverToRemove = _turnObservers.begin() + token;
        _turnObservers.erase(oberverToRemove);
    }
    bool ChessBoard::NotifyNextTurn()
    {
        return false;
    }
};