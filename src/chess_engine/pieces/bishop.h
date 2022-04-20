#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Bishop : public ChessPiece
	{
	public:

		Bishop(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Bishop, color, board) {}
		std::vector<base::Vector2d> generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}