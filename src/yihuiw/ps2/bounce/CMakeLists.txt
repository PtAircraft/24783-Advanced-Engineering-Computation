cmake_minimum_required(VERSION 3.7)
add_executable(bounce MACOSX_BUNDLE main.cpp)
target_link_libraries(bounce fslazywindow)