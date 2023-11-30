cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR ${PROJECT_SOURCE_DIR}/lib/SFML/sfml-install/lib/cmake/SFML/)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
include_directories("include/")

add_executable(CMakeSFMLProject src/main.cpp   "include/GameAsset.h"      "include/Boid.h" "src/Boid.cpp" "include/VectorUtils.h" "src/VectorUtils.cpp" "src/Flock.cpp" "include/Flock.h" "include/NeighborSearchStrategy.h" "src/NeighborSearchStrategy.cpp" "include/NaiveSearchStrategy.h" "src/NaiveSearchStrategy.cpp")

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/lib/SFML/sfml-install/bin/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()



install(TARGETS CMakeSFMLProject)
