#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Knight : public ChessPiece
	{
	public:
		Knight(PieceColor color, IChessBoardNotifier* board) : ChessPiece(ChessPieceType::Knight, color, board) {}
		std::vector<base::Vector2d> generatePossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}