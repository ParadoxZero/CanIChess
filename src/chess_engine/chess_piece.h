#pragma once

#include "../base/cordinate.h"
#include "chess_tritmap.h"

#include <vector>
#include <memory>

namespace chess_engine 
{
	class ChessBoard;

	enum ChessPieceType 
	{
		Empty,
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

		virtual std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, ChessBoard& board) = 0;
		virtual bool isValidMove(base::Cordinate from, base::Cordinate to, Tritmap &map) { return true; /*Incomplete - under development*/ };
	private:
		PieceColor _color;
		ChessPieceType _type;
	};

	class ChessPieceFactory
	{
	public:
		static std::unique_ptr<ChessPiece> createPiece(ChessPieceType, PieceColor);
		static std::unique_ptr<ChessPiece> ChessPieceFactory::createEmpty();

	};
}