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
        map[0][6] = TRITMAP_WHITE;
        auto move_list = pawn->getPossibleMoves({0,6}, map);

        ASSERT_EQ(move_list.size(), 2);
        base::Cordinate test_result{ 0,5 };
        EXPECT_EQ(move_list[0], test_result);
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, test_result, map));
        test_result = { 0,4 };
        EXPECT_EQ(move_list[1], test_result);
        EXPECT_TRUE(pawn->isValidMove({0,6}, test_result, map));

        map[1][5] = TRITMAP_BLACK;
        move_list = pawn->getPossibleMoves({ 0,6 }, map);

        ASSERT_EQ(move_list.size(), 3);
        test_result = {0, 5};
        EXPECT_EQ(move_list[0], test_result);
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, test_result, map));
        test_result = { 0,4 };
        EXPECT_EQ(move_list[1], test_result);
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, test_result, map));
        test_result = { 1,5 };
        EXPECT_EQ(move_list[2], test_result);
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, test_result, map));

        map = {};
        move_list = pawn->getPossibleMoves({ 0,0 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = TRITMAP_WHITE;
        map[2][2] = TRITMAP_WHITE;

        move_list = pawn->getPossibleMoves({ 2,3 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = TRITMAP_WHITE;
        map[2][2] = TRITMAP_BLACK;

        move_list = pawn->getPossibleMoves({ 2,3 }, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = TRITMAP_WHITE;
        map[2][2] = TRITMAP_EMPTY;

        move_list = pawn->getPossibleMoves({ 2,3 }, map);
        ASSERT_EQ(move_list.size(), 2);

        /* White pawn movement from 6 to 0 */
       
        map = {};
        map[2][3] = TRITMAP_WHITE;
        map[3][2] = TRITMAP_BLACK;
        map[1][2] = TRITMAP_BLACK;

        move_list = pawn->getPossibleMoves({ 2,3 }, map);
        ASSERT_EQ(move_list.size(), 4);

        std::vector<base::Cordinate> test_reference { {2,2},{2,1},{1,2},{3,2} };
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_EQ(move_list[2], test_reference[2]);
        EXPECT_EQ(move_list[3], test_reference[3]);
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[1], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[2], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[3], map));


        map = {};
        map[2][3] = TRITMAP_WHITE;
        map[3][2] = TRITMAP_WHITE;
        map[1][2] = TRITMAP_WHITE;

        move_list = pawn->getPossibleMoves({ 2,3 }, map);
        ASSERT_EQ(move_list.size(), 2);

        test_reference = { {2,2},{2,1} /*, {3,3},{1,3} */};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,3 }, test_reference[1], map));

        /* Black pawn movement from 0 to 6 */

        map = {};
        map[2][2] = TRITMAP_BLACK;
        map[3][3] = TRITMAP_WHITE;
        map[1][3] = TRITMAP_WHITE;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 4);

        test_reference = { {2,3},{2,4},{3,3},{1,3} };
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_EQ(move_list[2], test_reference[2]);
        EXPECT_EQ(move_list[3], test_reference[3]);
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[1], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[2], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[3], map));

        map = {};
        map[2][2] = TRITMAP_BLACK;
        map[3][3] = TRITMAP_BLACK;
        map[1][3] = TRITMAP_BLACK;

        move_list = pawn->getPossibleMoves({ 2,2 }, map);
        ASSERT_EQ(move_list.size(), 2);

        test_reference = { {2,3},{2,4} /*, {3,3},{1,3} */ };
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({ 2,2 }, test_reference[1], map));
    }

    TEST_F(ChessPiecesTest, TestPawnIsValidMove)
    {
        std::unique_ptr<ChessPiece> pawn = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        Tritmap map{};
        map[0][6] = TRITMAP_WHITE;
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, {0,5}, map));
        EXPECT_TRUE(pawn->isValidMove({ 0,6 }, { 0,4 }, map));
        map[0][0] = TRITMAP_BLACK;
        EXPECT_TRUE(pawn->isValidMove({ 0,0 }, { 0,2 }, map)); // Since from has changed, the catch will be recomputed.
    }

}