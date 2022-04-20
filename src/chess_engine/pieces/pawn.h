#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Pawn : public ChessPiece
	{
	public:

		Pawn(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Pawn, color, board) {}
		std::vector<base::Vector2d> generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}