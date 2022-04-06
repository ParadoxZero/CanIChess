#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_board.h"

#define BLACK(a) {a, Black}
#define WHITE(a) {a, White}
#define EMPTY {Empty, White}

namespace chess_engine
{
    struct Tile {
        ChessPieceType type;
        PieceColor color;
    };

    class MockObserver : IObserver
    {
    public:

        MOCK_METHOD(bool, NotifyNextTurn, (), (override));

        int count;
        MockObserver(int c) : count(c) {}
        MockObserver() {}
    };

    class ChessBoardTest : public ::testing::Test
    {
    public:
        std::vector<const IObserver*>& getTurnObservers(chess_engine::ChessBoard &board) { return board._turnObservers; }
        Tile getBoardState(chess_engine::ChessBoard &board,
            int i, int j) {
            return Tile{board._state[i][j]->getType(), board._state[i][j]->getColor()};
        }
    };

    TEST_F(ChessBoardTest, TestChessBoardInit)
    {
        chess_engine::ChessBoard board;
        Tile boardReference[8][8] = {
            {BLACK(Rook), BLACK(Bishop), BLACK(Knight), BLACK(Queen), BLACK(King), BLACK(Knight), BLACK(Bishop), BLACK(Rook)},
            {BLACK(Pawn), BLACK(Pawn),   BLACK(Pawn),   BLACK(Pawn),  BLACK(Pawn), BLACK(Pawn),   BLACK(Pawn),   BLACK(Pawn)},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {EMPTY,       EMPTY,         EMPTY,         EMPTY,        EMPTY,       EMPTY,         EMPTY,         EMPTY},
            {WHITE(Pawn), WHITE(Pawn),   WHITE(Pawn),   WHITE(Pawn),  WHITE(Pawn), WHITE(Pawn),   WHITE(Pawn),   WHITE(Pawn)},
            {WHITE(Rook), WHITE(Bishop), WHITE(Knight), WHITE(Queen), WHITE(King), WHITE(Knight), WHITE(Bishop), WHITE(Rook)},
        };

        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                Tile boardState = getBoardState(board, i, j);
                EXPECT_EQ(boardState.color, boardReference[i][j].color);
                EXPECT_EQ(boardState.type, boardReference[i][j].type);
            }
        }
    }

    TEST_F(ChessBoardTest, TestObserverMechanics)
    {
        chess_engine::ChessBoard board;
        MockObserver a(0), b(1);
        auto _turnObservers = getTurnObservers(board);
        EXPECT_EQ(_turnObservers.size(), 1);

        ChessBoard::ObserverRegistrationToken a_token = board.SubscribeToTurnNotification((IObserver*)(&a));
        _turnObservers = getTurnObservers(board);

        EXPECT_EQ(_turnObservers.size(), 2);
        EXPECT_EQ(a_token, 1);

        ChessBoard::ObserverRegistrationToken b_token = board.SubscribeToTurnNotification((IObserver*)(&b));
        _turnObservers = getTurnObservers(board);

        EXPECT_EQ(_turnObservers.size(), 3);
        EXPECT_EQ(b_token, 2); // Token of A.

        board.UnsubscribeToTurnNotification(a_token);
        _turnObservers = getTurnObservers(board);

        ASSERT_EQ(_turnObservers.size(), 2);

        auto last_observer = _turnObservers.back();
        const MockObserver* mock_observer = (const MockObserver*)(last_observer);

        ASSERT_TRUE(mock_observer != nullptr);
        EXPECT_EQ(mock_observer->count, 1); // B element should remain
    }
}