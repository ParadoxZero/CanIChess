#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Rook : public ChessPiece
	{
	public:

		Rook(PieceColor color) : ChessPiece(ChessPieceType::Rook, color) {}
		std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}