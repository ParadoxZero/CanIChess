#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Bishop : public ChessPiece
	{
	public:

		Bishop(PieceColor color) : ChessPiece(ChessPieceType::Bishop, color) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoardMatrix<ChessPiece>& map) override;
	};
}
}