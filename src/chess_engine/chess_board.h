#pragma once

#include "chess_piece.h"

#include <stdint.h>
#include <memory>

namespace chess_engine
{
	class ChessBoard
	{
	public:
		const uint8_t BOARD_SIZE = 8;

		void getState(std::unique_ptr<ChessPiece> state[][8]) { state = _state; }

	private:
		std::unique_ptr<ChessPiece> _state[8][8];
	};
}