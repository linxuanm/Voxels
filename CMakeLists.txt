cmake_minimum_required(VERSION 3.13)
project(Voxels)

set(CMAKE_CXX_STANDARD 14)

function(log_list LIST)
    foreach(element IN LISTS ${LIST})
        message("\t- ${element}")
    endforeach()
endfunction()

set(VOXELS_HEADERS
    src/gl.h

    src/game/application.h
    src/game/voxels.h

    src/util/config.h
    src/util/log.h
    src/util/specs.h

    src/render/view/camera.h
    src/render/shader/shader.h
)

set(VOXELS_SOURCES
    src/game/application.cpp
    src/game/voxels.cpp

    src/util/config.cpp
    src/util/log.cpp

    src/render/view/camera.cpp
    src/render/shader/shader.cpp
)

set(GLEW /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW /usr/local/Cellar/glfw/3.3.5/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW} ${GLFW})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Voxels main.cpp ${VOXELS_HEADERS} ${VOXELS_SOURCES})

include_directories(/usr/local/include/ src)

if (APPLE)
    target_link_libraries(Voxels "-framework OpenGL")
endif()
