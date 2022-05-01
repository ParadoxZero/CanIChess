#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/chess_engine/chess_piece.h"
#include "../src/base/result.h"

#include "../src/chess_engine/pieces/utils.h"

#include <unordered_set>

namespace chess_engine::pieces
{

    class ChessPiecesTest : public ::testing::Test
    {
    public:
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

        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> initMap()
        {
            std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map;
            for (int i = 0; i < map.size(); ++i)
            {
                for (int j = 0; j < map[i].size(); ++j)
                {
                    map[i][j] = ChessPieceFactory::createEmpty();
                }
            }
            return map;
        }
    };

    TEST_F(ChessPiecesTest, TestPawnGetAvailableMoves)
    {
        std::unique_ptr<ChessPiece> pawn = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map = initMap();
        map[0][6] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        auto move_list = pawn->generatePossibleMoves({0, 6}, map);

        ASSERT_EQ(move_list.size(), 2);
        base::Vector2Di test_result{0, 5};
        EXPECT_EQ(move_list[0], test_result);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, test_result, map));
        test_result = {0, 4};
        EXPECT_EQ(move_list[1], test_result);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, test_result, map));

        map[1][5] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        move_list = pawn->generatePossibleMoves({0, 6}, map);

        ASSERT_EQ(move_list.size(), 3);
        test_result = {0, 5};
        EXPECT_EQ(move_list[0], test_result);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, test_result, map));
        test_result = {0, 4};
        EXPECT_EQ(move_list[1], test_result);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, test_result, map));
        test_result = {1, 5};
        EXPECT_EQ(move_list[2], test_result);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, test_result, map));

        map = initMap();
        move_list = pawn->generatePossibleMoves({0, 0}, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        move_list = pawn->generatePossibleMoves({2, 3}, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        move_list = pawn->generatePossibleMoves({2, 3}, map);
        ASSERT_EQ(move_list.size(), 0);

        map = initMap();
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        move_list = pawn->generatePossibleMoves({2, 2}, map);
        ASSERT_EQ(move_list.size(), 0);

        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Empty, White);

        move_list = pawn->generatePossibleMoves({2, 3}, map);
        ASSERT_EQ(move_list.size(), 2);

        /* White pawn movement from 6 to 0 */

        map = initMap();
        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[3][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[1][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        move_list = pawn->generatePossibleMoves({2, 3}, map);
        ASSERT_EQ(move_list.size(), 4);

        std::vector<base::Vector2Di> test_reference{{2, 2}, {2, 1}, {1, 2}, {3, 2}};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_EQ(move_list[2], test_reference[2]);
        EXPECT_EQ(move_list[3], test_reference[3]);
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[1], map));
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[2], map));
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[3], map));

        map = initMap();
        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[3][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[1][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        move_list = pawn->generatePossibleMoves({2, 3}, map);
        ASSERT_EQ(move_list.size(), 2);

        test_reference = {{2, 2}, {2, 1} /*, {3,3},{1,3} */};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({2, 3}, test_reference[1], map));

        /* Black pawn movement from 0 to 6 */

        map = initMap();
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[1][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        move_list = pawn->generatePossibleMoves({2, 2}, map);
        ASSERT_EQ(move_list.size(), 4);

        test_reference = {{2, 3}, {2, 4}, {3, 3}, {1, 3}};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_EQ(move_list[2], test_reference[2]);
        EXPECT_EQ(move_list[3], test_reference[3]);
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[1], map));
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[2], map));
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[3], map));

        map = initMap();
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[1][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        move_list = pawn->generatePossibleMoves({2, 2}, map);
        ASSERT_EQ(move_list.size(), 2);

        test_reference = {{2, 3}, {2, 4} /*, {3,3},{1,3} */};
        EXPECT_EQ(move_list[0], test_reference[0]);
        EXPECT_EQ(move_list[1], test_reference[1]);
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[0], map));
        EXPECT_TRUE(pawn->isValidMove({2, 2}, test_reference[1], map));
    }

    TEST_F(ChessPiecesTest, TestPawnIsValidMove)
    {
        std::unique_ptr<ChessPiece> pawn = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map = initMap();
        map[0][6] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        EXPECT_TRUE(pawn->isValidMove({0, 6}, {0, 5}, map));
        EXPECT_TRUE(pawn->isValidMove({0, 6}, {0, 4}, map));
        map[0][0] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        EXPECT_TRUE(pawn->isValidMove({0, 0}, {0, 2}, map)); // Since 'from' has changed, the cache will be recomputed.
    }

    TEST_F(ChessPiecesTest, TestKnightGetAvailableMoves)
    {
        std::unique_ptr<ChessPiece> knight = ChessPieceFactory::createPiece(ChessPieceType::Knight, White);
        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map = initMap();
        std::vector<base::Vector2Di> test_results;
        std::vector<base::Vector2Di> return_vector;
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Knight, White);
        return_vector = knight->generatePossibleMoves({3, 3}, map);
        test_results = {{4, 5}, {2, 5}, {2, 1}, {4, 1}, {1, 2}, {5, 2}, {1, 4}, {5, 4}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        /* Knight at corner - Check for bounds */
        map = initMap();
        map[0][0] = ChessPieceFactory::createPiece(ChessPieceType::Knight, White);
        return_vector = knight->generatePossibleMoves({0, 0}, map);
        test_results = {
            {1, 2},
            {2, 1},
        };
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        /* Knight blocked by friendly tiles */
        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Knight, White);

        map[5][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[1][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[5][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[1][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[4][1] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[4][5] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][1] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][5] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        return_vector = knight->generatePossibleMoves({3, 3}, map);
        test_results = {};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        /* Knight blocked by friendly tiles and enemy */
        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Knight, White);

        map[5][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[1][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[5][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[1][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        map[4][1] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[4][5] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][1] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][5] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        return_vector = knight->generatePossibleMoves({3, 3}, map);
        test_results = {{1, 2}, {5, 2}, {1, 4}, {5, 4}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));
    }

    TEST_F(ChessPiecesTest, TestKingGetAvailableMoves)
    {
        std::unique_ptr<ChessPiece> king = ChessPieceFactory::createPiece(ChessPieceType::King, White);
        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map = initMap();
        std::vector<base::Vector2Di> test_results;
        std::vector<base::Vector2Di> return_vector;

        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(King, White);
        return_vector = king->generatePossibleMoves({3, 3}, map);
        test_results = {{4, 3}, {4, 4}, {3, 4}, {2, 4}, {2, 3}, {2, 2}, {3, 2}, {4, 2}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        map = initMap();
        map[3][0] = ChessPieceFactory::createPiece(King, White);
        return_vector = king->generatePossibleMoves({3, 0}, map);
        test_results = {{4, 0}, {4, 1}, {3, 1}, {2, 1}, {2, 0}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        map = initMap();
        map[0][0] = ChessPieceFactory::createPiece(King, White);
        return_vector = king->generatePossibleMoves({0, 0}, map);
        test_results = {{1, 0}, {1, 1}, {0, 1}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(King, White);

        map[4][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        map[4][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[4][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        return_vector = king->generatePossibleMoves({3, 3}, map);
        test_results = {{4, 3}, {3, 4}, {2, 2}, {3, 2}};
        EXPECT_TRUE(AreEqual(return_vector, test_results));

        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(King, White);

        map[4][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[2][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);
        map[3][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, Black);

        map[4][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][4] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[2][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        map[4][2] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        return_vector = king->generatePossibleMoves({3, 3}, map);
        test_results = {{4, 3}, {3, 4}, {2, 2}, {3, 2}, {1, 1}};
        EXPECT_FALSE(AreEqual(return_vector, test_results));
    }

    TEST_F(ChessPiecesTest, TestDirectionalMove)
    {
        std::vector<base::Vector2Di> results;
        std::array<std::array<std::unique_ptr<ChessPiece>, 8>, 8> map = initMap();
        map[0][0] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);

        results = getPossibleMovesInDirection({0, 0}, {{0, 1}}, map);
        EXPECT_TRUE(AreEqual(results, {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}}));

        map[0][1] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        results = getPossibleMovesInDirection({0, 0}, {{0, 1}}, map);
        EXPECT_TRUE(AreEqual(results, {}));
        EXPECT_FALSE(AreEqual(results, {{0, 1}}));

        map = initMap();
        map[0][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        results = getPossibleMovesInDirection({0, 3}, {{0, 1}, {0, -1}}, map);
        EXPECT_TRUE(AreEqual(results, {{0, 0}, {0, 1}, {0, 2}, {0, 4}, {0, 5}, {0, 6}, {0, 7}}));

        map = initMap();
        map[3][3] = ChessPieceFactory::createPiece(ChessPieceType::Pawn, White);
        results = getPossibleMovesInDirection({3, 3}, {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}}, map);
        EXPECT_TRUE(AreEqual(results, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {2, 4}, {1, 5}, {0, 6}, {2, 2}, {1, 1}, {0, 0}, {4, 2}, {5, 1}, {6, 0}}));
    }

}