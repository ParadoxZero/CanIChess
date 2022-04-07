#include "chess_board.h"
#include "chess_piece.h"
#include "../base/result.h"

#include <memory>

using namespace std;
using namespace base;

#define BLACK(a) ChessPieceFactory::createPiece(a, Black)
#define WHITE(a) ChessPieceFactory::createPiece(a, White)
#define EMPTY ChessPieceFactory::createEmpty()

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
        SyncBitmapCache();
    }

    std::array<std::array<int8_t, 8>, 8> ChessBoard::getColormap()
    {
        return _cachedTritmap;
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

    Result ChessBoard::playMove(base::Cordinate from, base::Cordinate to)
    {
        auto subject = _state[from.y][from.x].get();
        if (subject->getColor() != getCurrentColor())
        {
            return Result::InvalidArgument;
        }
        if (!subject->isValidMove(from, to, _cachedTritmap))
        {
            return Result::InvalidArgument;
        }

        _state[to.y][to.x] = move(_state[from.y][from.x]);
        _state[from.y][from.x] = ChessPieceFactory::createEmpty();
        _moveHistory.push_back({ { from.x,from.y }, { to.x, to.y } });
        _cachedTritmap[to.y][to.x] = subject->getColor() == White ? TRITMAP_WHITE : TRITMAP_BLACK;
        _cachedTritmap[from.y][from.x] = TRITMAP_EMPTY;

        return Result::Success;
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
        return true;
    }

    void ChessBoard::SyncBitmapCache()
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (_state[i][j]->getType() != Empty)
                {
                    _cachedTritmap[i][j] = _state[i][j]->getColor() == White ? TRITMAP_WHITE : TRITMAP_BLACK;
                }
                else
                {
                    _cachedTritmap[i][j] = TRITMAP_EMPTY;
                }
            }
        }
    }
};