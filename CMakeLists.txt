# minimum required version
cmake_minimum_required(VERSION 3.10)
project(lasernet)

# set c++ language standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs")

# add modules path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# dependent packages
find_package(TensorFlow REQUIRED)

# set executable
set(LSNET "${PROJECT_SOURCE_DIR}/lasernet")
set(LSNET_SRC "${LSNET}/src/main")

# set include directories
include_directories("${LSNET}/include/")
include_directories(${TensorFlow_INCLUDE_DIRS})

add_executable(lasernet ${LSNET_SRC})
target_link_libraries(lasernet ${TensorFlow_LIBRARIES})
