cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(SOURCE_FILES 
	test_main.cpp
 "chess_engine_tests.cpp" "chess_piece_tests.cpp")

add_executable(${BINARY} ${SOURCE_FILES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(LINK_TARGETS
	CanIChess
	chess_engine
	gtest
	gmock
)
target_link_libraries(${BINARY} PUBLIC ${LINK_TARGETS})