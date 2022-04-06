#pragma once

#include "chess_piece.h"

#include <stdint.h>
#include <memory>
#include <vector>
#include <array>

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
        static const int8_t BITMAP_BLACK = -1;
        static const int8_t BITMAP_WHITE = 1;
        static const int8_t BITMAP_EMPTY = 0;

        ChessBoard();

        const uint8_t BOARD_SIZE = 8;

        void getState(std::unique_ptr<ChessPiece> state[][8]) { state = _state; }
        std::array<std::array<int8_t,8>, 8> getColormap();

        PieceColor getCurrentColor();
        void playMove(base::Cordinate from, base::Cordinate to);
        std::vector<base::Cordinate> getPossibleMoves(base::Cordinate from);

        ObserverRegistrationToken SubscribeToTurnNotification(const IObserver *observer);
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token);

        bool NotifyNextTurn() override;

    private:
        friend class ChessBoardTest;

        std::unique_ptr<ChessPiece> _state[8][8];
        std::array<std::array<int8_t, 8>, 8> _cachedBitmap;
        std::vector<const IObserver*> _turnObservers;

        void SyncBitmapCache();
    };
}