#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Knight : public ChessPiece
	{
	public:
		Knight(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Knight, color, board) {}
		std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) override;
	};
}
}