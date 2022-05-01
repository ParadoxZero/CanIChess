#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Bishop : public ChessPiece
	{
	public:

		Bishop(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Bishop, color, board) {}
		std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) override;
	};
}
}