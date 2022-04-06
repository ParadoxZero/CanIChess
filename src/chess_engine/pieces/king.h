#include "../chess_piece.h"

namespace chess_engine {
namespace pieces {
	class King : public ChessPiece
	{
		std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoard& board) override;
	};
}
}