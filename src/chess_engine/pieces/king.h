#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class King : public ChessPiece
	{
	public:
		King(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::King, color, board) {}
		std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) override;
	};
}
}