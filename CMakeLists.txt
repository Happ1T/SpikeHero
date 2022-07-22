cmake_minimum_required(VERSION 3.22)
project(NewGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp hero.h consts.h view.h entity.h enemy.h tinyxml2.h tinyxml2.cpp levl.h bars.h game.h menu.h options.h texture.h save.h network.h networkserver.h networkserverclient.h pause_menu.h)
add_executable(NewGame ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(NewGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
