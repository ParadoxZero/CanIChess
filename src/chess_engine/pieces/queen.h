#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Queen : public ChessPiece
	{
	public:

		Queen(PieceColor color) : ChessPiece(ChessPieceType::Queen, color) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoard& board) override;
	};
}
}