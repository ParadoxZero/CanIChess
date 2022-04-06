#pragma once

#include "chess_piece.h"

#include <memory>

namespace chess_engine
{
	class Tile
	{
	public:
		bool isEmpty() { return _isEmpty; }
		PieceColor tileColor() { return _piece->getColor(); }
		ChessPieceType pieceType() { return _piece->getType(); }

		class Client
		{
			ChessPiece* releaseChessPiece(Tile& tile) { tile._piece.release(); }
			void setTile(Tile& tile, ChessPiece* piece) { tile._piece.reset(piece); }
			Tile* createTile(ChessPiece* _piece)
			{
				std::unique_ptr<Tile> tile = std::make_unique<Tile>();
				tile->_piece.reset(_piece);
				if (_piece == nullptr)
				{
					tile->_isEmpty = true;
				}
				return tile.release();
			}
		};

	private:
		bool _isEmpty;
		std::unique_ptr<ChessPiece> _piece;
	};
}