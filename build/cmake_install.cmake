# Install script for directory: /Users/ptaircraft/24783/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/ptaircraft/24783/build/public/src/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps2/cannonball/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps2/bounce/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/simplebitmap/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/utility/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps3/ps3_1/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps3/ps3_2/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps4/ps4_1/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps4/ps4_2/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/naca/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps5/ps5_1/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps5/ps5_2/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/binaryStlViewer/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps6/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps7/ps7_1/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps7/ps7_2/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps8/ps8_1/cmake_install.cmake")
  include("/Users/ptaircraft/24783/build/yihuiw/ps8/ps8_2/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/ptaircraft/24783/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
