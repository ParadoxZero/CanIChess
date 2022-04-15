#include "../chess_piece.h"

namespace chess_engine {
namespace pieces 
{
	class Pawn : public ChessPiece
	{
	public:

		Pawn(PieceColor color) : ChessPiece(ChessPieceType::Pawn, color), _cachedFrom(INVALID) {}
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, Tritmap& map) override;
		bool isValidMove(base::Cordinate from, base::Cordinate to, Tritmap& map);
		bool NextTurnEvent();

	private:
		std::vector<base::Cordinate> _cachedMoves;
		base::Cordinate _cachedFrom;

		static const base::Cordinate INVALID;
	};
}
}