#pragma once

#include "../base/cordinate.h"
#include "chess_tritmap.h"
#include "chess_board_listener.h"

#include <vector>
#include <memory>

namespace chess_engine 
{
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

	class ChessPiece : IObserver
	{
	public:
		ChessPiece(ChessPieceType type, PieceColor color) : 
			_type(type), 
			_color(color), 
			_board(nullptr), 
			_registrationToken(0) 
		{}

		ChessPiece(ChessPieceType type, PieceColor color, IChessBoardNotifier* board): ChessPiece(type, color) 
		{
			if (board)
			{
				_registrationToken = board->SubscribeToTurnNotification(this);
				_board = board;
			}
		}

		ChessPieceType getType() { return _type; };
		PieceColor getColor() { return _color; }

		virtual std::vector<base::Cordinate> getPossibleMoves(base::Cordinate current_position, Tritmap& map) = 0;
		virtual bool isValidMove(base::Cordinate from, base::Cordinate to, Tritmap &map) { return true; /*Incomplete - To be implemented by children*/ };
		virtual bool NextTurnEvent() { return true; }

		~ChessPiece()
		{
			if (_board)
			{
				_board->UnsubscribeToTurnNotification(_registrationToken);
			}
		}
	private:

		friend class ChessPiecesTest;

		PieceColor _color;
		ChessPieceType _type;
		ObserverRegistrationToken _registrationToken;
		IChessBoardNotifier* _board;
	};

	class ChessPieceFactory
	{
	public:
		static std::unique_ptr<ChessPiece> createPiece(ChessPieceType, PieceColor);
		static std::unique_ptr<ChessPiece> createEmpty();

	};
}