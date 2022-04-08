# CMakeList.txt : CMake project for CanIChess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES 
	base/cordinate.h
	base/result.h
	base/base.cpp
)

# Add source to this project's executable.
add_executable (game "main.cpp")
add_library(CanIChess STATIC ${SOURCE_FILES})

add_subdirectory("chess_engine")

set(LINK_TARGETS
	sfml-window
	chess_engine
	CanIChess
	imgui
)
target_link_libraries(game PRIVATE ${LINK_TARGETS})


# TODO: Add tests and install targets if needed.
