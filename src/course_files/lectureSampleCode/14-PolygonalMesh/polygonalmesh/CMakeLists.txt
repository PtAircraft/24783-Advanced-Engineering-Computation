add_library(polygonalmesh polygonalmesh.cpp polygonalmesh.h polygonalmeshio.cpp lattice.h meshlattice.h meshlattice.cpp)
target_include_directories(polygonalmesh PUBLIC .)
target_link_libraries(polygonalmesh ysclass)


add_executable(test_polygonalmesh main.cpp)
target_link_libraries(test_polygonalmesh polygonalmesh)
