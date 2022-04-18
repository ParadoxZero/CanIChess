#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class King : public ChessPiece
	{
	public:
		King(PieceColor color) : ChessPiece(ChessPieceType::King, color) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}