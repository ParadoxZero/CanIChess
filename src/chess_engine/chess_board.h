#pragma once

#include "chess_piece.h"
#include "chess_board_listener.h"
#include "../base/result.h"

#include <stdint.h>
#include <memory>
#include <vector>
#include <array>

namespace chess_engine
{

    class ChessBoard : public IObserver, public IChessBoardNotifier
    {
    public:
        ChessBoard();

        const uint8_t BOARD_SIZE = 8;

        ChessBoardMatrix<ChessPiece> getState();

        PieceColor getCurrentColor();
        base::Result playMove(base::Cordinate from, base::Cordinate to);
        std::vector<base::Cordinate> getPossibleMoves(base::Cordinate from);

        ObserverRegistrationToken SubscribeToTurnNotification(IObserver *observer) override;
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token) override;
        bool NextTurnEvent() override;

    private:
        friend class ChessBoardTest;

        ChessBoardMatrix<ChessPiece> _state;
        std::vector<IObserver*> _turnObservers;
        std::vector<std::pair<base::Cordinate, base::Cordinate>> _moveHistory;

        bool NotifyNextTurn();
    };
}