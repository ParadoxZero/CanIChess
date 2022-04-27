#pragma once

#include "chess_piece.h"
#include "chess_board_listener.h"
#include "../base/result.h"

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include <array>

namespace chess_engine
{

    class ChessBoard : public IObserver, public IChessBoardNotifier
    {
    public:
        ChessBoard();

        ChessBoard(const ChessBoard&) = delete;

        const uint8_t BOARD_SIZE = 8;

        ChessBoardMatrix<ChessPiece> getState();

        PieceColor getCurrentColor();
        base::Result playMove(base::Vector2d from, base::Vector2d to);
        std::vector<base::Vector2d> getPossibleMoves(base::Vector2d from);

        ObserverRegistrationToken SubscribeToTurnNotification(IObserver *observer) override;
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token) override;
        bool NextTurnEvent() override;

        bool PromotePawn(ChessPieceType to);

    private:
        friend class ChessBoardTest;

        ChessBoardMatrix<ChessPiece> _state;
        std::vector<IObserver*> _turnObservers;
        std::vector<std::pair<base::Vector2d, base::Vector2d>> _moveHistory;
        std::unique_ptr<base::Vector2d> _promotionCandidate = nullptr;

        bool NotifyNextTurn();

        bool Check(base::Vector2d from);
        bool Checkmate();
        bool Promote(base::Vector2d from);
    };
}