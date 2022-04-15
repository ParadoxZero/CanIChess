#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_board.h"
#include "../src/chess_engine/chess_tritmap.h"
#include "../src/base/result.h"

#define BLACK(a) {a, Black}
#define WHITE(a) {a, White}
#define EMPTY {Empty, White}

namespace chess_engine
{
    using namespace chess_engine;

    struct Tile {
        ChessPieceType type;
        PieceColor color;
    };

    class MockObserver : public IObserver
    {
    public:

        MOCK_METHOD(bool, NextTurnEvent, (), (override));

        int count;
        MockObserver(int c) : count(c) {}
        MockObserver() {}
    };

    class ChessBoardTest : public ::testing::Test
    {
    public:
        std::vector<IObserver*>& getTurnObservers(ChessBoard &board) { return board._turnObservers; }
        Tile getBoardState(ChessBoard &board,
            int i, int j) {
            return Tile{board._state[i][j]->getType(), board._state[i][j]->getColor()};
        }

        size_t getBoardHistorySize(ChessBoard& board)
        {
            return board._moveHistory.size();
        }
    };

    TEST_F(ChessBoardTest, TestChessBoardInit)
    {
        chess_engine::ChessBoard board;
        Tile boardReference[8][8] = {
            {BLACK(Rook),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Rook)},
            {BLACK(Bishop), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Bishop)},
            {BLACK(Knight), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Knight)},
            {BLACK(King),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Queen)},
            {BLACK(Queen),  BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(King)},
            {BLACK(Knight), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Knight)},
            {BLACK(Bishop), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Bishop)},
            {BLACK(Rook),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Rook)},
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

        std::array<std::array<int8_t, 8>, 8> map = board.getColormap();

        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (boardReference[i][j].type == Empty)
                {
                    EXPECT_EQ(map[i][j], chess_engine::TRITMAP_EMPTY);
                }
                else {
                    EXPECT_EQ(map[i][j], boardReference[i][j].color == PieceColor::White? chess_engine::TRITMAP_WHITE : chess_engine::TRITMAP_BLACK);
                }
            }
        }
    }

    TEST_F(ChessBoardTest, TestPlayMove)
    {
        ChessBoard board;
        MockObserver observer;
        MockObserver* observer_ptr = &observer;
        board.SubscribeToTurnNotification(observer_ptr);
        EXPECT_CALL(observer, NextTurnEvent).Times(3);

        // Valid Move - moving a white tile in first move
        EXPECT_EQ(board.getCurrentColor(), White);
        EXPECT_NE(board.getCurrentColor(), Black);
        EXPECT_EQ(board.playMove({ 0,6 }, { 0, 5}), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 1);
        
        Tritmap map = board.getColormap();
        EXPECT_EQ(map[0][5], TRITMAP_WHITE);
        EXPECT_EQ(map[0][6], TRITMAP_EMPTY);

        // Invalid Move - Moving white tile while black's turn
        EXPECT_EQ(board.playMove({ 1,6 }, { 1,5 }), base::Result::InvalidArgument);
        EXPECT_EQ(getBoardHistorySize(board), 1);
        map = board.getColormap();

        EXPECT_EQ(map[1][5], TRITMAP_EMPTY);
        EXPECT_EQ(map[1][6], TRITMAP_WHITE);

        // Valid Move - Moving black tile
        EXPECT_EQ(board.playMove({ 0,1 }, { 0,2 }), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 2);

        map = board.getColormap();
        EXPECT_EQ(map[0][1], TRITMAP_EMPTY);
        EXPECT_EQ(map[0][2], TRITMAP_BLACK);

        // Valid Move - Moving white again in next turn
        EXPECT_EQ(board.getCurrentColor(), White);
        EXPECT_NE(board.getCurrentColor(), Black);
        EXPECT_EQ(board.playMove({ 1,6 }, { 1,5 }), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 3);

        map = board.getColormap();
        EXPECT_EQ(map[1][5], TRITMAP_WHITE);
        EXPECT_EQ(map[1][6], TRITMAP_EMPTY);

        // invalid Move - moving a black tile in first move
        ChessBoard board2;
        EXPECT_EQ(board2.getCurrentColor(), White);
        EXPECT_NE(board2.getCurrentColor(), Black);
        EXPECT_EQ(board2.playMove({ 0,1 }, { 0,2 }), base::Result::InvalidArgument);
        EXPECT_EQ(getBoardHistorySize(board2), 0);

        map = board2.getColormap();
        EXPECT_EQ(map[0][1], TRITMAP_BLACK);
        EXPECT_EQ(map[0][2], TRITMAP_EMPTY);

    }

    TEST_F(ChessBoardTest, TestObserverMechanics)
    {
        chess_engine::ChessBoard board;
        MockObserver a(0), b(1);
        auto _turnObservers = getTurnObservers(board);
        EXPECT_EQ(_turnObservers.size(), 1);

        ObserverRegistrationToken a_token = board.SubscribeToTurnNotification((IObserver*)(&a));
        _turnObservers = getTurnObservers(board);

        EXPECT_EQ(_turnObservers.size(), 2);
        EXPECT_EQ(a_token, 1);

        ObserverRegistrationToken b_token = board.SubscribeToTurnNotification((IObserver*)(&b));
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