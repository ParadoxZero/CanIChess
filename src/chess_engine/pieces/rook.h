#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Rook : public ChessPiece
	{
	public:

		Rook(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Rook, color, board) {}
		std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) override;
	};
}
}