# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CanIChess")

include(CTest)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

include_directories(
	"src"
	"deps/sfml/include"
	"deps/gtest/googletest/include"
	"deps/gtest/googlemock/include"
	"deps/imgui"
	"Deps/imgui-sfml"
)

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("test")

set(BUILD_SHARED_LIBS OFF)
set(SFML_USE_SYSTEM_DEPS OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
add_subdirectory("deps/sfml")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("deps/gtest")

add_subdirectory("deps/imgui")

set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR "../imgui")
set(IMGUI_SFML_USE_DEFAULT_CONFIG OFF)
set(IMGUI_SFML_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(IMGUI_SFML_CONFIG_NAME "imconfig.h")
add_subdirectory("deps/imgui-sfml")