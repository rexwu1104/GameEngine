cmake_minimum_required(VERSION 3.12)
project("GameEngine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

include_directories(include)

add_executable(GameEngine
        src/GameEngine.cpp
        src/Backend.cpp
        src/gui/GUI.cpp
        src/gui/GUIEvent.cpp
        src/gui/Window.cpp)

add_library(Win_Utils STATIC
        src/platform/win32/WindowHandle.cpp
        src/platform/win32/opengl/init.cpp)

function(target_add_library target)
    add_library(GameEngine_${target}_Backend_static STATIC ${ARGN})
    add_library(GameEngine_${target}_Backend_shared SHARED ${ARGN})
endfunction()

function(target_add_links target target_name)
    include_directories(${${target_name}_INCLUDE_DIR})
    target_link_libraries(GameEngine_${target}_Backend_static PRIVATE ${${target_name}_LIBRARIES})
    target_link_libraries(GameEngine_${target}_Backend_shared PRIVATE ${${target_name}_LIBRARIES})
    target_compile_definitions(GameEngine PRIVATE ${target}_ENABLE)
    target_link_libraries(GameEngine PRIVATE GameEngine_${target}_Backend_static)
    if (WIN32)
        target_link_libraries(GameEngine PRIVATE Win_Utils)
        target_link_libraries(GameEngine_${target}_Backend_static PRIVATE Win_Utils)
        target_link_libraries(GameEngine_${target}_Backend_shared PRIVATE Win_Utils)
        target_link_libraries(Win_Utils PRIVATE ${${target_name}_LIBRARIES})
    endif ()
endfunction()

set(OpenGL_Backend_Files
        src/backend/opengl/main.cpp)
set(DirectX_Backend_Files
        src/backend/directx/main.cpp)
set(Metal_Backend_Files
        src/backend/metal/main.cpp)
set(Vulkan_Backend_Files
        src/backend/vulkan/main.cpp)

set(WINDOWS_SDK_PATH "$ENV{ProgramFiles\(x86\)}/Windows Kits/10")
find_path(DirectX_INCLUDE_DIR d3d12.h PATHS "${WINDOWS_SDK_PATH}/Include/")
find_library(DirectX_LIBRARIES d3d12.lib PATHS "${WINDOWS_SDK_PATH}/Lib/")

message(${DirectX_INCLUDE_DIR})
message(${DirectX_LIBRARIES})

find_package(OpenGL QUIET)
find_package(Vulkan QUIET)
find_library(METAL_FRAMEWORK Metal)
set(Metal_INCLUDE_DIR ${METAL_FRAMEWORK})
set(Metal_LIBRARIES ${METAL_FRAMEWORK})

string(COMPARE NOTEQUAL "${METAL_FRAMEWORK}" "METAL_FRAMEWORK-NOTFOUND" Metal_FOUND)
string(COMPARE NOTEQUAL "${DirectX_INCLUDE_DIR}" "" I_FOUND)
string(COMPARE NOTEQUAL "${DirectX_LIBRARIES}" "" L_FOUND)
math(EXPR DirectX_FOUND "${I_FOUND} & ${L_FOUND}")

#get_cmake_property(all_vars VARIABLES)
#foreach(var ${all_vars})
#    message(STATUS "${var} = ${${var}}")
#endforeach()

if (OpenGL_FOUND)
    target_add_library(OpenGL ${OpenGL_Backend_Files})
    target_add_links(OpenGL OPENGL)
endif ()

if (Vulkan_FOUND)
    target_add_library(Vulkan ${Vulkan_Backend_Files})
    target_add_links(Vulkan Vulkan)
endif ()

if (APPLE AND Metal_FOUND)
    target_add_library(Metal ${Metal_Backend_Files})
    target_add_links(Metal Metal)
endif ()

if (WIN32 AND MSVC AND DirectX_FOUND)
    target_add_library(DirectX ${DirectX_Backend_Files})
    target_add_links(DirectX DirectX)
    include_directories(
            "${DirectX_INCLUDE_DIR}/../shared"
            "${DirectX_INCLUDE_DIR}/../ucrt")
endif ()

if (NOT OpenGL_FOUND AND
    NOT Vulkan_FOUND AND
    NOT Metal_FOUND AND
    NOT DirectX_FOUND)
    message(FATAL_ERROR "NOT graphic API FOUND")
endif ()