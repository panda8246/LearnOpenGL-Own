cmake_minimum_required(VERSION 3.6)

project(imgui LANGUAGES CXX)

set(SOURCES_IMGUI 
    "imgui.cpp"
    "imgui.h"
    "imconfig.h"
    "imgui_demo.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
    "imgui_internal.h"
    "imstb_rectpack.h"
    "imstb_textedit.h"
    "imstb_truetype.h")

add_library(imgui STATIC ${SOURCES_IMGUI})
target_include_directories(imgui PUBLIC "src/")

set_target_properties(imgui PROPERTIES
            		  CXX_STANDARD 17
            		  CXX_EXTENSIONS OFF)