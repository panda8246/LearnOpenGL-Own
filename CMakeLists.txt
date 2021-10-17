cmake_minimum_required(VERSION 3.6)

project(LearnOpenGL-OWN)

set(SOURCE_STB_IMAGE
    "deps/stb_image/stb_image.h"
    "deps/stb_image/stb_image.cpp"
)

set(SOURCE_MAIN 
    "src/shader.h"
    "src/main.cpp"
)

set(SOURCE 
    ${SOURCE_STB_IMAGE}
    ${SOURCE_MAIN}
)

add_executable(LearnOpenGL ${SOURCE})


include_directories(deps)
include_directories(deps/stb_image)
include_directories(src)

#glad
add_subdirectory("deps/glad" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glad)

#glfw
add_subdirectory("deps/glfw" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glfw)

#glm
add_subdirectory("deps/glm" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE glm)

#imgui
add_subdirectory("deps/imgui" EXCLUDE_FROM_ALL)
target_link_libraries(LearnOpenGL PRIVATE imgui)


#复制Shader
#参考 https://minecraftxwinp.github.io/2017/11/27/%E7%94%A8CMake%E5%9C%A8%E5%BB%BA%E7%BD%AE%E6%99%82%E8%A4%87%E8%A3%BD%E6%AA%94%E6%A1%88%E5%88%B0%E8%BC%B8%E5%87%BA%E5%9F%B7%E8%A1%8C%E6%AA%94%E7%9A%84%E7%9B%AE%E9%8C%84/
add_custom_target(
    # 自訂的目標名稱
    copy_shader_files
    # 執行copy指令 cmake -E copy <file>... destination 
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/shader ${CMAKE_CURRENT_BINARY_DIR}/shader
    #复制贴图(待定)
)

# 用add_dependencies將自訂目標列為建置目標的dependency
add_dependencies(LearnOpenGL copy_shader_files)


#纹理不是常修改的东西，放在cmake阶段复制就好
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

