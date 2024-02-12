cmake_minimum_required(VERSION 3.14)
project(numberium CXX)
add_subdirectory(${vivid_ROOT_DIR} ${vivid_ROOT_DIR})
add_executable(game
    src/Game.cpp
    src/Main.cpp
    src/Common/Common.cpp
    src/Common/Vector.cpp
    src/Collision/Collision.cpp
    src/Collision/DrawCollision.cpp
    src/Pictures/Fonts.cpp
    src/Pictures/Textures.cpp
    src/Pictures/Pictures.cpp
    src/Pictures/Camera.cpp
    src/Stage/Stage.cpp
    src/Numbers/Numbers.cpp
)
find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_ttf)
target_link_libraries(game SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf vivid)