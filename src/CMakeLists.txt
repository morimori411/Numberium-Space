cmake_minimum_required(VERSION 3.14)
project(numberium CXX)
add_executable(game
    Game.cpp
    Main.cpp
    Common/Common.cpp
    Common/Vector.cpp
    Collision/Collision.cpp
    Collision/DrawCollision.cpp
    Pictures/Fonts.cpp
    Pictures/Textures.cpp
    Pictures/Pictures.cpp
    Pictures/Camera.cpp
    Stage/Stage.cpp
    Numbers/Numbers.cpp
)
find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_ttf)
target_link_libraries(game SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)