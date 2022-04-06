#pragma once

#include "base/cordinate.h"

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

	enum PieceColor
	{
		White,
		Black
	};

	class ChessPiece
	{
	public:
		ChessPiece(ChessPieceType type, PieceColor color) : _type(type), _color(color) {}
		ChessPieceType getType() { return _type; };
		PieceColor getColor() { return _color; }

		virtual std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position) = 0;
	private:
		PieceColor _color;
		ChessPieceType _type;
	};

	class ChessPieceFactory
	{
	public:
		static ChessPiece* createPiece(ChessPieceType, PieceColor);
	};
}