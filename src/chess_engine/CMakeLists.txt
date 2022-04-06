cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME chess_engine)

set(SOURCE_FILES
	"base/cordinate.h"
	"chess_board.h"
	"chess_board.cc"
	"chess_piece.h"
	"chess_piece_factory.cpp"
	"pieces/king.h"
	"pieces/king.cc"
	"pieces/queen.h"
	"pieces/queen.cc"
	"pieces/bishop.h"
	"pieces/bishop.cc"
	"pieces/knight.h"
	"pieces/knight.cc"
	"pieces/rook.h"
	"pieces/rook.cc"
	"pieces/pawn.h"
	"pieces/pawn.cc"
	"pieces/empty.h"
	"pieces/empty.cc"
)

add_library(chess_engine STATIC ${SOURCE_FILES})