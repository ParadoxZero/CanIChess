# CMakeList.txt : CMake project for CanIChess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES 
	main.cpp
)

# Add source to this project's executable.
add_executable (CanIChess ${SOURCE_FILES})

add_subdirectory("chess_engine")

set(LINK_TARGETS
	sfml-window
	chess_engine
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_TARGETS})


# TODO: Add tests and install targets if needed.
