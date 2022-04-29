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
		static std::unique_ptr<ChessPiece> createPiece(ChessPieceType, PieceColor,  IChessBoardNotifier * board = nullptr);
		static std::unique_ptr<ChessPiece> createEmpty();

	};

	class ChessPiece : IObserver
	{
	public:
		ChessPiece(ChessPieceType type, PieceColor color, IChessBoardNotifier* board = nullptr): 
			_type(type), 
			_color(color), 
			_board(board), 
			_registrationToken(0),
			_cachedFrom(INVALID),
			_cachedMoves({}) 
		{
			if (board)
			{
				_registrationToken = board->SubscribeToTurnNotification(this);
				_board = board;
			}
		}

		ChessPieceType getType() { return _type; };
		PieceColor getColor() { return _color; }

		virtual std::vector<base::Vector2Di> generatePossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map, bool ignore_friendly = false) = 0;
		virtual std::vector<base::Vector2Di> getAllMoves(base::Vector2Di from, ChessBoardMatrix<ChessPiece>& map);

		std::vector<base::Vector2Di> getPossibleMoves(base::Vector2Di current_position, ChessBoardMatrix<ChessPiece>& map);
		bool isValidMove(base::Vector2Di from, base::Vector2Di to, ChessBoardMatrix<ChessPiece>& map);
		bool NextTurnEvent() override;

		std::unique_ptr<ChessPiece> Clone() { return ChessPieceFactory::createPiece(_type, _color); }

		virtual ~ChessPiece();
	private:

		friend class ChessPiecesTest;
		friend class ChessBoardTest;

		PieceColor _color;
		ChessPieceType _type;
		ObserverRegistrationToken _registrationToken;
		IChessBoardNotifier* _board;

	protected:
		std::vector<base::Vector2Di> _cachedMoves;
		base::Vector2Di _cachedFrom;
		static const base::Vector2Di INVALID;
	};
}