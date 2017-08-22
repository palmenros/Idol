cmake_minimum_required(VERSION 3.8)
project(Idol)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        sandbox/entry.cpp
        core/id/Types.h
        core/id/utils/FileUtils.cpp
        core/id/utils/FileUtils.h
        core/Idol.h
        core/id/Common.h
        core/id/Math.h
        core/id/graphics/Shader.h
        core/id/graphics/Shader.cpp
        core/id/app/Application.cpp
        core/id/app/Application.h
        core/id/app/Window.cpp
        core/id/app/Window.h
        core/id/utils/VFS.cpp
        core/id/utils/VFS.h
        sandbox/Sandbox.h
        core/id/OpenGL.h
        dependencies/stb_image.h
        core/id/graphics/Texture.cpp
        core/id/graphics/Texture.h
        core/id/graphics/VertexArray.cpp
        core/id/graphics/VertexArray.h
        core/id/graphics/Buffer.cpp
        core/id/graphics/Buffer.h
        core/id/graphics/BufferLayout.cpp
        core/id/graphics/BufferLayout.h
        core/id/graphics/Camera.cpp
        core/id/graphics/Camera.h
        core/id/graphics/IndexBuffer.cpp
        core/id/graphics/IndexBuffer.h
        )

add_executable(Idol ${SOURCE_FILES})

#libOpenGL.so libGLEW.so libglut.so libglfw.so
target_link_libraries(Idol libOpenGL.so libglfw.so libGLEW.so)
include_directories(
        core
        dependencies
)

add_definitions(
    -DDEBUG
    -D__PROJECT_DIR__="/home/pedro/CLionProjects/Idol/"
)