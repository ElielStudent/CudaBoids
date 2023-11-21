cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR ${PROJECT_SOURCE_DIR}/SFML/sfml-install/lib/cmake/SFML/)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
include_directories("include/")

add_executable(CMakeSFMLProject src/main.cpp "include/Boid.h" "include/LogicEntity.h" "include/GameAsset.h" "include/Sprite.h" "src/Boid.cpp" )

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/SFML/sfml-install/bin/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
