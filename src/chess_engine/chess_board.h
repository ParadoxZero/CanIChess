#pragma once

#include "chess_piece.h"
#include "chess_board_listener.h"
#include "chess_tritmap.h"
#include "../base/result.h"

#include <stdint.h>
#include <memory>
#include <vector>
#include <array>

namespace chess_engine
{
    class ChessBoardTest;

    class ChessBoard : public IObserver, public IChessBoardNotifier
    {
    public:
        ChessBoard();

        const uint8_t BOARD_SIZE = 8;

        void getState(std::unique_ptr<ChessPiece> state[][8]) { state = _state; }
        std::array<std::array<int8_t,8>, 8> getColormap();

        PieceColor getCurrentColor();
        base::Result playMove(base::Cordinate from, base::Cordinate to);
        std::vector<base::Cordinate> getPossibleMoves(base::Cordinate from);

        ObserverRegistrationToken SubscribeToTurnNotification(IObserver *observer) override;
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token) override;
        bool NextTurnEvent() override;

    private:
        friend class ChessBoardTest;

        std::unique_ptr<ChessPiece> _state[8][8];
        Tritmap _cachedTritmap;
        std::vector<IObserver*> _turnObservers;
        std::vector<std::pair<base::Cordinate, base::Cordinate>> _moveHistory;

        void SyncBitmapCache();
        bool NotifyNextTurn();
    };
}