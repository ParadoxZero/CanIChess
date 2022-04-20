cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME renderer)

set(SFML_SOURCES
	"backend/sfml/sfml_window.h"
	"backend/sfml/sfml_window.cpp")

set(SOURCE_FILES
	${SFML_SOURCES}
	"api/window.h"
	"renderer_factory.cpp"
	"api/wrapper.h" 
	"api/event.h")

add_library(renderer STATIC ${SOURCE_FILES})

set(LINK_TARGETS
	sfml-window
	sfml-system
	sfml-graphics
	sfml-audio
	imgui
	ImGui-SFML
	OpenGL
)
target_link_libraries(renderer PRIVATE ${LINK_TARGETS})