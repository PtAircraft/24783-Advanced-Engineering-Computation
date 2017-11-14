add_library(qem qem.cpp qem.h)
target_link_libraries(qem geblkernel)
target_include_directories(qem PUBLIC .)


add_executable(shellext_sample MACOSX_BUNDLE main.cpp glutil.cpp glutil.h shelllattice.h shelllattice.cpp)
target_link_libraries(shellext_sample fslazywindow ysclass geblkernel polygonalmesh qem)
