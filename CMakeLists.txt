cmake_minimum_required(VERSION 3.13)
project(Voxels)

set(CMAKE_CXX_STANDARD 14)

function(log_list LIST)
    foreach(element IN LISTS ${LIST})
        message("\t- ${element}")
    endforeach()
endfunction()

set(VOXELS_HEADERS)
set(VOXELS_SOURCES)

set(GLEW /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW} ${GLFW})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Voxels main.cpp ${VOXELS_HEADERS} ${VOXELS_SOURCES})

include_directories(src)

if (APPLE)
    target_link_libraries(Voxels "-framework OpenGL")
endif()
