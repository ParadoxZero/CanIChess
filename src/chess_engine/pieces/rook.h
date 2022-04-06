#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Rook : public ChessPiece
	{
	public:

		Rook(PieceColor color) : ChessPiece(ChessPieceType::Rook, color) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoard& board) override;
	};
}
}