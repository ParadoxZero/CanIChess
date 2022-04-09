#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_piece.h"
#include "../src/chess_engine/chess_tritmap.h"
#include "../src/base/result.h"

#include "../src/chess_engine/pieces/pawn.h"

namespace chess_engine::pieces {

    class ChessPiecesTest : public ::testing::Test
    {

    };

    TEST_F(ChessPiecesTest, TestPawnGetAvailableMoves)
    {
        std::unique_ptr<ChessPiece> pawn = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        Tritmap map{};
        map[0][0] = TRITMAP_WHITE;
        auto move_list = pawn->getPossibleMoves({0,0}, map);
        base::Cordinate test_result{ 0,1 };

        ASSERT_EQ(move_list.size(), 2);
        EXPECT_EQ(move_list[0], test_result);
        test_result = { 0,2 };
        EXPECT_EQ(move_list[1], test_result);

        map[1][1] = TRITMAP_BLACK;
        move_list = pawn->getPossibleMoves({ 0,0 }, map);

        ASSERT_EQ(move_list.size(), 3);
        test_result = {0, 1};
        EXPECT_EQ(move_list[0], test_result);
        test_result = { 0,2 };
        EXPECT_EQ(move_list[1], test_result);
        test_result = { 1,1 };
        EXPECT_EQ(move_list[2], test_result);

        map = {};
        move_list = pawn->getPossibleMoves({ 0,0 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][2] = TRITMAP_WHITE;
        map[2][3] = TRITMAP_WHITE;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][2] = TRITMAP_WHITE;
        map[2][3] = TRITMAP_BLACK;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][2] = TRITMAP_WHITE;
        map[2][3] = TRITMAP_EMPTY;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 2);
       
        map = {};
        map[2][2] = TRITMAP_WHITE;
        map[3][3] = TRITMAP_BLACK;
        map[1][3] = TRITMAP_BLACK;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 4);

        std::vector<base::Cordinate> test_reference { {2,3},{2,4},{3,3},{1,3} };
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_EQ(move_list[2], test_reference[2]);
        EXPECT_EQ(move_list[3], test_reference[3]);

        map = {};
        map[2][2] = TRITMAP_WHITE;
        map[3][3] = TRITMAP_WHITE;
        map[1][3] = TRITMAP_WHITE;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 2);

        test_reference = { {2,3},{2,4} /*, {3,3},{1,3} */};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
    }
}