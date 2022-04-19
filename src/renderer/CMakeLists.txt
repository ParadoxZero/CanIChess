cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME renderer)

set(SOURCE_FILES
	"api/window.h"
	"renderer_factory.cpp"
	"api/wrapper.h" 
	"api/event.h")

add_library(renderer STATIC ${SOURCE_FILES})