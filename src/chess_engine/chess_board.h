#pragma once

#include "chess_piece.h"
#include "../base/result.h"

#include <stdint.h>
#include <memory>
#include <vector>
#include <array>
#include "chess_tritmap.h"

namespace chess_engine
{
    class ChessBoardTest;

    class IObserver
    {
    public:
        virtual bool NotifyNextTurn() = 0;
    };

    class ChessBoard : IObserver
    {
    public:
        typedef size_t ObserverRegistrationToken;

        ChessBoard();

        const uint8_t BOARD_SIZE = 8;

        void getState(std::unique_ptr<ChessPiece> state[][8]) { state = _state; }
        std::array<std::array<int8_t,8>, 8> getColormap();

        PieceColor getCurrentColor();
        base::Result playMove(base::Cordinate from, base::Cordinate to);
        std::vector<base::Cordinate> getPossibleMoves(base::Cordinate from);

        ObserverRegistrationToken SubscribeToTurnNotification(const IObserver *observer);
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token);

        bool NotifyNextTurn() override;

    private:
        friend class ChessBoardTest;

        std::unique_ptr<ChessPiece> _state[8][8];
        Tritmap _cachedTritmap;
        std::vector<const IObserver*> _turnObservers;
        std::vector<std::pair<base::Cordinate, base::Cordinate>> _moveHistory;

        void SyncBitmapCache();
    };
}