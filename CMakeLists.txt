# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CanIChess")

include(CTest)

include_directories(
	"deps/sfml/include"
	"deps/gtest/googletest/include"
	"deps/gtest/googlemock/include"
)

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("test")

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory("deps/sfml")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("deps/gtest")