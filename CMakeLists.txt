cmake_minimum_required(VERSION 3.14)
project(numberium CXX)
add_subdirectory(${morimori_sdl_ROOT_DIR} ${morimori_sdl_ROOT_DIR})
add_subdirectory(${vivid_ROOT_DIR} ${vivid_ROOT_DIR})
add_executable(game
    src/Main.cpp
    src/Stage/Stage.cpp
    src/Numbers/Numbers.cpp
)
target_compile_options(
  game PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Wextra>
  $<$<CXX_COMPILER_ID:MSVC>: /W4>
)
find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_ttf)
target_link_libraries(game SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf vivid morimori_sdl)