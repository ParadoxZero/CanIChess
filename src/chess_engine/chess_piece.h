#pragma once

#include "../base/cordinate.h"
#include "chess_board_listener.h"

#include <vector>
#include <memory>
#include <array>

namespace chess_engine 
{
	template<class T> using ChessBoardMatrix = std::array<std::array<std::unique_ptr<T>, 8>, 8>;

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

	class ChessPiece;

	class ChessPieceFactory
	{
	public:
		static std::unique_ptr<ChessPiece> createPiece(ChessPieceType, PieceColor);
		static std::unique_ptr<ChessPiece> createEmpty();

	};

	class ChessPiece : IObserver
	{
	public:
		ChessPiece(ChessPieceType type, PieceColor color) : 
			_type(type), 
			_color(color), 
			_board(nullptr), 
			_registrationToken(0),
			_cachedFrom(INVALID),
			_cachedMoves({})
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

		virtual std::vector<base::Vector2d> getPossibleMoves(base::Vector2d current_position, ChessBoardMatrix<ChessPiece>& map) = 0;
		bool isValidMove(base::Vector2d from, base::Vector2d to, ChessBoardMatrix<ChessPiece>& map);
		bool NextTurnEvent() override;

		std::unique_ptr<ChessPiece> Clone() { return ChessPieceFactory::createPiece(_type, _color); }

		virtual ~ChessPiece();
	private:

		friend class ChessPiecesTest;

		PieceColor _color;
		ChessPieceType _type;
		ObserverRegistrationToken _registrationToken;
		IChessBoardNotifier* _board;

	protected:
		std::vector<base::Vector2d> _cachedMoves;
		base::Vector2d _cachedFrom;
		static const base::Vector2d INVALID;
	};
}