#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_board.h"

namespace chess_engine
{
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
        chess_engine::ChessBoard board;
        std::vector<const IObserver*>& getTurnObservers() { return board._turnObservers; }
    };

    TEST_F(ChessBoardTest, TestObserverMechanics)
    {
        MockObserver a(0), b(1);
        auto _turnObservers = getTurnObservers();
        EXPECT_EQ(_turnObservers.size(), 1);

        ChessBoard::ObserverRegistrationToken a_token = board.SubscribeToTurnNotification((IObserver*)(&a));
        _turnObservers = getTurnObservers();

        EXPECT_EQ(_turnObservers.size(), 2);
        EXPECT_EQ(a_token, 1);

        ChessBoard::ObserverRegistrationToken b_token = board.SubscribeToTurnNotification((IObserver*)(&b));
        _turnObservers = getTurnObservers();

        EXPECT_EQ(_turnObservers.size(), 3);
        EXPECT_EQ(b_token, 2); // Token of A.

        board.UnsubscribeToTurnNotification(a_token);
        _turnObservers = getTurnObservers();

        ASSERT_EQ(_turnObservers.size(), 2);

        auto last_observer = _turnObservers.back();
        const MockObserver* mock_observer = (const MockObserver*)(last_observer);

        ASSERT_TRUE(mock_observer != nullptr);
        EXPECT_EQ(mock_observer->count, 1); // B element should remain
    }
}