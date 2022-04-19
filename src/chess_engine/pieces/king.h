#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class King : public ChessPiece
	{
	public:
		King(PieceColor color) : ChessPiece(ChessPieceType::King, color) {}
		std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}