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
        sandbox/Sandbox.h)

add_executable(Idol ${SOURCE_FILES})

#libOpenGL.so libGLEW.so libglut.so libglfw.so
target_link_libraries(Idol libOpenGL.so libglfw.so libGLEW.so)
include_directories(core)

add_definitions(-DDEBUG)