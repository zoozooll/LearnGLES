cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -funwind-tables")

project("learngles")

include_directories("." "./model")

# Add glm library
add_subdirectory("../thirdparty/glm" ${CMAKE_CURRENT_BINARY_DIR}/glm)
include_directories("${glm_SOURCE_DIR}")

# Add stb_image library
include_directories("../thirdparty/stb")

# Add assimp library
set(ASSIMP_ANDROID_JNIIOSYSTEM ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

set(ASSIMP_SRC "../thirdparty/assimp")
add_subdirectory(${ASSIMP_SRC} ${CMAKE_CURRENT_BINARY_DIR}/assimp)

# Add Freetype Library
set(FT_DISABLE_ZLIB TRUE CACHE BOOL "Disable Zlib")
set(FT_DISABLE_BZIP2 TRUE CACHE BOOL "Disable BZip2")
set(FT_DISABLE_PNG TRUE CACHE BOOL "Disable PNG")
set(FT_DISABLE_HARFBUZZ TRUE CACHE BOOL "Disable HarfBuzz")
set(FT_DISABLE_BROTLI TRUE CACHE BOOL "Disable Brotli")

add_subdirectory("../thirdparty/freetype" ${CMAKE_CURRENT_BINARY_DIR}/freetype)

file(GLOB learngles_SRC
        "./*.cpp"
        "./model/*.cpp"
        "./basic/*.cpp"
        "./lighting/*.cpp"
        "./pbr/*.cpp"
        "./advanced/*.cpp"
        )

add_library(learngles SHARED ${learngles_SRC})

find_library(log-lib log)

target_link_libraries(
        learngles
        GLESv3
        android
        EGL
        atomic
        jnigraphics
        glm
        assimp
        freetype
        ${log-lib})
