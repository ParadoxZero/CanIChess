#pragma once

#include "chess_piece.h"
#include "tile_state.h"

#include <stdint.h>

namespace chess_engine
{
	class ChessBoard : private Tile::Client
	{
	public:
		const uint8_t BOARD_SIZE = 8;

		void getState(Tile state[][8]) { state = _boardState; }

	private:
		Tile _boardState[8][8];

	};
}