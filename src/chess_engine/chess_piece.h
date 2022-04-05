#include "base/chess_move.h"

#include <vector>

namespace chess_engine 
{
	enum ChessPieceType 
	{
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King
	};

	class ChessPiece
	{
	public:
		virtual std::vector<base::ChessMove> getPossibleMoves() = 0;
	};
}