cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -funwind-tables")

project("nativegl")

include_directories(".")

# Add glm library
#add_subdirectory("../thirdparty/glm" ${CMAKE_CURRENT_BINARY_DIR}/glm)
include_directories("${glm_SOURCE_DIR}")

# Add stb_image library
include_directories("../thirdparty/stb")

# Add assimp library
option("ASSIMP_ANDROID_JNIIOSYSTEM", ON)
option("ASSIMP_BUILD_TEST", OFF)
option("ASSIMP_INJECT_DEBUG_POSTFIX", OFF)
set(ASSIMP_SRC "../thirdparty/assimp")

add_subdirectory(${ASSIMP_SRC} ${CMAKE_CURRENT_BINARY_DIR}/assimp)

file(GLOB nativegl_SRC
        "./*.cpp"
        "./1_getting_started/*.cpp"
        "./2_lighting/*.cpp"
        "./3_model_loading/*.cpp"
        "./4_advanced_opengl/*.cpp"
        "./5_advanced_lighting/*.cpp"
        "./6_pbr/*.cpp"
        "./7_in_practice/*.cpp"
        "./8_guest/*.cpp"
        )

add_library(nativegl SHARED ${nativegl_SRC})

find_library(log-lib log)

target_link_libraries(
        nativegl
        GLESv3
        android
        EGL
        atomic
        jnigraphics
        glm
        assimp
        ${log-lib})