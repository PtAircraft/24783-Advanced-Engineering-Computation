cmake_minimum_required(VERSION 3.7)
add_executable(view MACOSX_BUNDLE main.cpp)
target_link_libraries(view fslazywindow naca4digit utility)