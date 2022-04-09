#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Knight : public ChessPiece
	{
	public:
		Knight(PieceColor color) : ChessPiece(ChessPieceType::Knight, color) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, Tritmap& map) override;
	};
}
}