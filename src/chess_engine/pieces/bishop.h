#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Bishop : public ChessPiece
	{
	public:

		Bishop(PieceColor color) : ChessPiece(ChessPieceType::Bishop, color) {}
		std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}