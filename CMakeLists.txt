# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CanIChess")

include_directories(
	"deps/sfml/include",
)

# Include sub-projects.
add_subdirectory ("CanIChess")

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory("deps/sfml")