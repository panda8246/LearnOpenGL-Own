cmake_minimum_required(VERSION 3.6)

project(LearnOpenGL)

set(SOURCE_MAIN 
    "src/main.cpp"
)

set(SOURCE 
    ${SOURCE_MAIN}
)

add_executable(LearnOpenGL ${SOURCE})

include_directories("/deps")
include_directories("/src")

#glad
add_subdirectory("deps/glad" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glad)

#glfw
add_subdirectory("deps/glfw" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glfw)

#glm
add_subdirectory("deps/glm" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glm)


