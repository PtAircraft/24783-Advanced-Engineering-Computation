set(TARGET_NAME ps6)
add_library(ps6lib ps6lib.cpp ps6lib.h)
target_link_libraries(ps6lib geblkernel utility fslazywindow)
target_include_directories(ps6lib PUBLIC .)

add_executable(ps6 main.cpp)
target_link_libraries(ps6 ps6lib)
