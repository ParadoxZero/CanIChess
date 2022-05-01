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
        base::Result playMove(base::Vector2Di from, base::Vector2Di to);
        std::vector<base::Vector2Di> getPossibleMoves(base::Vector2Di from);

        ObserverRegistrationToken SubscribeToTurnNotification(IObserver *observer) override;
        void UnsubscribeToTurnNotification(ObserverRegistrationToken token) override;
        bool NextTurnEvent() override;

        bool PromotePawn(ChessPieceType to);

    private:
        friend class ChessBoardTest;

        ChessBoardMatrix<ChessPiece> _state;
        std::vector<IObserver*> _turnObservers;
        std::vector<std::pair<base::Vector2Di, base::Vector2Di>> _moveHistory;
        std::unique_ptr<base::Vector2Di> _promotionCandidate = nullptr;

        bool NotifyNextTurn();

        bool Check(base::Vector2Di from);
        bool Checkmate();
        bool Promote(base::Vector2Di from);
    };
}