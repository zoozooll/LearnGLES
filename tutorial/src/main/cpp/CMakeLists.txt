cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -funwind-tables")

project("learngles")

include_directories(".")

# Add glm library
add_subdirectory("../thirdparty/glm" ${CMAKE_CURRENT_BINARY_DIR}/glm)
include_directories("${glm_SOURCE_DIR}")

# Add stb_image library
include_directories("../thirdparty/stb")

# Add assimp library
option("ASSIMP_ANDROID_JNIIOSYSTEM", ON)
option("ASSIMP_BUILD_TEST", OFF)
option("ASSIMP_INJECT_DEBUG_POSTFIX", OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_SRC "../thirdparty/assimp")

add_subdirectory(${ASSIMP_SRC} ${CMAKE_CURRENT_BINARY_DIR}/assimp)

file(GLOB learngles_SRC
        "./*.cpp"
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
        ${log-lib})