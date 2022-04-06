#include "chess_board.h"

namespace chess_engine
{
    ChessBoard::ChessBoard()
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