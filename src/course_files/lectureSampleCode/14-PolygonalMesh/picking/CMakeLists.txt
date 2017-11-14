add_executable(mesh_picking MACOSX_BUNDLE main.cpp glutil.cpp glutil.h)
target_link_libraries(mesh_picking fslazywindow ysclass polygonalmesh)
