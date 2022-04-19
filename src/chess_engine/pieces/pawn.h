#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Pawn : public ChessPiece
	{
	public:

		Pawn(PieceColor color) : ChessPiece(ChessPieceType::Pawn, color) {}
		std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}