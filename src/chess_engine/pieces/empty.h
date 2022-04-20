#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Empty : public ChessPiece
	{
	public:

		Empty() : ChessPiece(ChessPieceType::Empty, /* Not Relevant */ PieceColor::White) {}
		std::vector<base::Vector2d> generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}