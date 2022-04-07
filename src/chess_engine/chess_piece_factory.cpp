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
	std::unique_ptr<ChessPiece> ChessPieceFactory::createPiece(ChessPieceType type, PieceColor color)
	{
		switch (type)
		{
		case ChessPieceType::King:		return std::unique_ptr<ChessPiece>(new pieces::King(color));
		case ChessPieceType::Queen:		return std::unique_ptr<ChessPiece>(new pieces::Queen(color));
		case ChessPieceType::Bishop:	return std::unique_ptr<ChessPiece>(new pieces::Bishop(color));
		case ChessPieceType::Knight:	return std::unique_ptr<ChessPiece>(new pieces::Knight(color));
		case ChessPieceType::Rook:		return std::unique_ptr<ChessPiece>(new pieces::Rook(color));
		case ChessPieceType::Pawn:		return std::unique_ptr<ChessPiece>(new pieces::Pawn(color));
		default:
			break;
		}
	}

	std::unique_ptr<ChessPiece> ChessPieceFactory::createEmpty()
	{
		return std::unique_ptr<ChessPiece>(new pieces::Empty());
	}
}