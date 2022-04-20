#include "chess_piece.h"

#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/rook.h"
#include "pieces/pawn.h"
#include "pieces/empty.h"

#include <memory>

namespace chess_engine
{
	class ChessBoard;
	
	std::unique_ptr<ChessPiece> ChessPieceFactory::createPiece(ChessPieceType type, PieceColor color, IChessBoardNotifier* board)
	{
		switch (type)
		{
		case ChessPieceType::King:		return std::unique_ptr<ChessPiece>(new pieces::King(color, board));
		case ChessPieceType::Queen:		return std::unique_ptr<ChessPiece>(new pieces::Queen(color, board));
		case ChessPieceType::Bishop:	return std::unique_ptr<ChessPiece>(new pieces::Bishop(color, board));
		case ChessPieceType::Knight:	return std::unique_ptr<ChessPiece>(new pieces::Knight(color, board));
		case ChessPieceType::Rook:		return std::unique_ptr<ChessPiece>(new pieces::Rook(color, board));
		case ChessPieceType::Pawn:		return std::unique_ptr<ChessPiece>(new pieces::Pawn(color, board));
		case ChessPieceType::Empty:
		default:
			return std::unique_ptr<ChessPiece>(new pieces::Empty());
		}
	}

	std::unique_ptr<ChessPiece> ChessPieceFactory::createEmpty()
	{
		return std::unique_ptr<ChessPiece>(new pieces::Empty());
	}
}