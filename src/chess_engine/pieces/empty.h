#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Empty : public ChessPiece
	{
	public:

		Empty() : ChessPiece(ChessPieceType::Empty, /* Not Relevant */ PieceColor::White) {}
		std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) override;
	};
}
}