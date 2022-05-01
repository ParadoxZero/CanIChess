#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_board.h"
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

        std::vector< std::pair<base::Vector2Di, base::Vector2Di> > getHistory(ChessBoard& board)
        {
            return board._moveHistory;
        }

        std::vector<base::Vector2Di> getCachedMoves(ChessBoard& board, base::Vector2Di from)
        {
            return board._state[from.x][from.y]->_cachedMoves;
        }

        bool check(ChessBoard& board, base::Vector2Di from)
        {
            return board.Check(from);
        }

        bool AreEqual(std::vector<base::Vector2Di> a, std::vector<base::Vector2Di> b)
        {
            for (auto i : a)
            {
                if (std::find(b.begin(), b.end(), i) == b.end())
                {
                    return false;
                }
            }

            for (auto i : b)
            {
                if (std::find(a.begin(), a.end(), i) == a.end())
                {
                    return false;
                }
            }

            return a.size() == b.size(); // [aabc] [abcd]
        }

    };

    TEST_F(ChessBoardTest, TestChessBoardInit)
    {
        chess_engine::ChessBoard board;
        Tile boardReference[8][8] = {
            {BLACK(Rook),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Rook)},
            {BLACK(Bishop), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Bishop)},
            {BLACK(Knight), BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Knight)},
            {BLACK(Queen),  BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(Queen)},
            {BLACK(King),   BLACK(Pawn), EMPTY, EMPTY, EMPTY, EMPTY, WHITE(Pawn),  WHITE(King)},
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

        auto map = board.getState();

        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (boardReference[i][j].type == Empty)
                {
                    EXPECT_EQ(map[i][j]->getType(), Empty);
                }
                else {
                    EXPECT_EQ(map[i][j]->getColor(), boardReference[i][j].color);
                }
            }
        }
    }

    TEST_F(ChessBoardTest, TestPlayMove)
    {
        ChessBoard board;
        MockObserver observer;
        MockObserver* observer_ptr = &observer;
        std::vector<base::Vector2Di> test_results;
        std::vector<base::Vector2Di> return_vector;
        board.SubscribeToTurnNotification(observer_ptr);
        EXPECT_CALL(observer, NextTurnEvent).Times(3);

        std::vector< std::pair<base::Vector2Di, base::Vector2Di> > history_reference;

        // Valid Move - moving a white tile in first move
        EXPECT_EQ(board.getCurrentColor(), White);
        EXPECT_NE(board.getCurrentColor(), Black);
        return_vector = board.getPossibleMoves({0,6});
        test_results = {{0,5}, {0,4}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        return_vector = getCachedMoves(board, {0,6});
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        EXPECT_EQ(board.playMove({ 0,6 }, { 0, 5}), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 1);
        auto history = getHistory(board);
        history_reference = { {{0,6},{0,5}} };
        EXPECT_EQ(history, history_reference);
        
        auto map = board.getState();
        EXPECT_EQ(map[0][5]->getColor(), White);
        EXPECT_EQ(map[0][6]->getType(), Empty);

        // Invalid Move - Moving white tile while black's turn
        EXPECT_EQ(board.playMove({ 1,6 }, { 1,5 }), base::Result::InvalidArgument);
        EXPECT_EQ(getBoardHistorySize(board), 1);
        history = getHistory(board);
        history_reference = { {{0,6},{0,5}} };
        EXPECT_EQ(history, history_reference);

        map = board.getState();
        EXPECT_EQ(map[1][5]->getType(), Empty);
        EXPECT_EQ(map[1][6]->getColor(), White);

        // Valid Move - Moving black tile
        EXPECT_EQ(board.playMove({ 0,1 }, { 0,2 }), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 2);
        history = getHistory(board);
        history_reference = { {{0,6},{0,5}}, {{ 0,1 }, { 0,2 }} };
        EXPECT_EQ(history, history_reference);

        map = board.getState();
        EXPECT_EQ(map[0][1]->getType(), Empty);
        EXPECT_EQ(map[0][2]->getColor(), Black);

        // Valid Move - Moving white again in next turn
        EXPECT_EQ(board.getCurrentColor(), White);
        EXPECT_NE(board.getCurrentColor(), Black);
        return_vector = board.getPossibleMoves({1,6});
        test_results = {{1,5}, {1,4}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        return_vector = getCachedMoves(board, {1,6});
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        EXPECT_EQ(board.playMove({ 1,6 }, { 1,5 }), base::Result::Success);
        EXPECT_EQ(getBoardHistorySize(board), 3);
        history = getHistory(board);
        history_reference = { {{0,6},{0,5}}, {{ 0,1 },{ 0,2 }}, {{ 1,6 }, { 1,5 }} };
        EXPECT_EQ(history, history_reference);

        map = board.getState();
        EXPECT_EQ(map[1][5]->getColor(), White);
        EXPECT_EQ(map[1][6]->getType(), Empty);

        // invalid Move - moving a black tile in first move
        ChessBoard board2;
        EXPECT_EQ(board2.getCurrentColor(), White);
        EXPECT_NE(board2.getCurrentColor(), Black);
        EXPECT_EQ(board2.playMove({ 0,1 }, { 0,2 }), base::Result::InvalidArgument);
        EXPECT_EQ(getBoardHistorySize(board2), 0);

        map = board2.getState();
        EXPECT_EQ(map[0][1]->getColor(), Black);
        EXPECT_EQ(map[0][2]->getType(), Empty);

        // invalid Move - moving a white pawn incorrectly in first move
        EXPECT_EQ(board2.getCurrentColor(), White);
        EXPECT_NE(board2.getCurrentColor(), Black);
        EXPECT_EQ(board2.playMove({ 0,6 }, { 0,3 }), base::Result::InvalidArgument);
        EXPECT_EQ(getBoardHistorySize(board2), 0);

        map = board2.getState();
        EXPECT_EQ(map[0][6]->getColor(), White);
        EXPECT_EQ(map[0][3]->getType(), Empty);

    }

    TEST_F(ChessBoardTest, TestObserverMechanics)
    {
        chess_engine::ChessBoard board;
        MockObserver a(0), b(1);
        auto _turnObservers = getTurnObservers(board);
        EXPECT_EQ(_turnObservers.size(), 33);

        ObserverRegistrationToken a_token = board.SubscribeToTurnNotification((IObserver*)(&a));
        _turnObservers = getTurnObservers(board);

        EXPECT_EQ(_turnObservers.size(), 34);
        EXPECT_EQ(a_token, 33);

        ObserverRegistrationToken b_token = board.SubscribeToTurnNotification((IObserver*)(&b));
        _turnObservers = getTurnObservers(board);

        EXPECT_EQ(_turnObservers.size(), 35);
        EXPECT_EQ(b_token, 34); // Token of A.

        board.UnsubscribeToTurnNotification(a_token);
        _turnObservers = getTurnObservers(board);

        ASSERT_EQ(_turnObservers.size(), 34);

        auto last_observer = _turnObservers.back();
        const MockObserver* mock_observer = (const MockObserver*)(last_observer);

        ASSERT_TRUE(mock_observer != nullptr);
        EXPECT_EQ(mock_observer->count, 1); // B element should remain
    }

    TEST_F(ChessBoardTest, TestMoveCachingMechanics)
    {
        ChessBoard board;
        std::vector<base::Vector2Di> test_results;
        std::vector<base::Vector2Di> return_vector;

        return_vector = board.getPossibleMoves({0,6});
        test_results = {{0,5}, {0,4}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        return_vector = getCachedMoves(board, {0,6});
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        EXPECT_EQ(board.playMove({ 0,6 }, { 0, 5}), base::Result::Success);
        return_vector = getCachedMoves(board, {0,6});
        test_results = {};
        EXPECT_TRUE(AreEqual(return_vector, test_results));
        
    }

    TEST_F(ChessBoardTest, TestFoolsmate)
    {
        ChessBoard board;

        EXPECT_EQ(board.playMove({ 5,6 }, { 5,4 }), base::Result::Success);
        EXPECT_EQ(board.playMove({ 4,1 }, { 4,2 }), base::Result::Success);
        EXPECT_EQ(board.playMove({ 6,6 }, { 6,4 }), base::Result::Success);
        EXPECT_EQ(board.playMove({ 3,0 }, { 7,4 }), base::Result::Checkmate);
    }
}