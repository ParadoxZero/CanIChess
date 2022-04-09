#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Empty : public ChessPiece
	{
	public:

		Empty() : ChessPiece(ChessPieceType::Empty, /* Not Relevant */ PieceColor::White) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, Tritmap& map) override;
	};
}
}