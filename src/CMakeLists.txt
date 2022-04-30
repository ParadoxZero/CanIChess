# CMakeList.txt : CMake project for CanIChess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES 
	base/cordinate.h
	base/result.h
	base/base.cpp
 	"base/cordinate.cpp"
	"base/config.h"
 )

# Add source to this project's executable.
add_executable (game "main.cpp")
add_library(CanIChess STATIC ${SOURCE_FILES})

add_subdirectory("chess_engine")
add_subdirectory("renderer")

set(LINK_TARGETS
	chess_engine
	renderer
	CanIChess
	imgui
)
target_link_libraries(game PRIVATE ${LINK_TARGETS})


# TODO: Add tests and install targets if needed.
