cmake_minimum_required(VERSION 3.13)
project(Voxels)

set(CMAKE_CXX_STANDARD 17)

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
    src/util/input.h
    src/util/runnable_queue.h
    src/util/image_display.h

    src/render/model/model.h
    src/render/texture.h
    src/render/view/camera.h
    src/render/view/buffer_builder.h
    src/render/shader/shader.h
    src/render/world/blockface.h
    src/render/world/render_chunk.h
    src/render/world/world_renderer.h

    src/math/blockpos.h
    src/math/vec.h
    src/math/noise.h

    src/world/chunk.h
    src/world/blocks.h
    src/world/world.h
    src/world/generator.h
    src/world/loading_thread.h

    src/player/controller.h
)

set(VOXELS_SOURCES
    src/game/application.cpp
    src/game/voxels.cpp

    src/util/config.cpp
    src/util/log.cpp
    src/util/input.cpp
    src/util/runnable_queue.cpp
    src/util/image_display.cpp

    src/render/model/model.cpp
    src/render/texture.cpp
    src/render/view/camera.cpp
    src/render/view/buffer_builder.cpp
    src/render/shader/shader.cpp
    src/render/world/blockface.cpp
    src/render/world/render_chunk.cpp
    src/render/world/world_renderer.cpp

    src/math/blockpos.cpp
    src/math/vec.cpp
    src/math/noise.cpp

    src/world/chunk.cpp
    src/world/blocks.cpp
    src/world/world.cpp
    src/world/generator.cpp
    src/world/loading_thread.cpp

    src/player/controller.cpp
)

message("\nIncluded headers:")
log_list(VOXELS_HEADERS)

message("\nIncluded headers:")
log_list(VOXELS_HEADERS)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
link_libraries(${OPENGL} ${GLEW_LIBRARIES} glfw)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Voxels main.cpp ${VOXELS_HEADERS} ${VOXELS_SOURCES})

include_directories(/usr/local/include/ src)

if (APPLE)
    target_link_libraries(Voxels "-framework OpenGL")
endif()
