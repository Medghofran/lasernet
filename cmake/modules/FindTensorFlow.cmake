# Locates the tensorFlow library and include directories.
include(FindPackageHandleStandardArgs)
unset(TENSORFLOW_FOUND)

find_path(
  TensorFlow_INCLUDE_DIR
  NAMES tensorflow/core tensorflow/cc third_party
  HINTS /usr/include/tensorflow /usr/local/include/tensorflow)

find_library(
  TensorFlowFW_LIBRARY
  NAMES tensorflow_framework
  HINTS /usr/lib /usr/local/lib)

find_library(
  TensorFlowCC_LIBRARY
  NAMES tensorflow_cc
  HINTS /usr/lib /usr/local/lib)

find_library(
  TensorFlow_LIBRARY
  NAMES tensorflow
  HINTS /usr/lib /usr/local/lib)

message(STATUS "Tensorflow Library Found ${TensorFlow_LIBRARY}")

# set TensorFlow_FOUND
find_package_handle_standard_args(
  TensorFlow DEFAULT_MSG TensorFlow_INCLUDE_DIR TensorFlow_LIBRARY
  TensorFlowCC_LIBRARY TensorFlowFW_LIBRARY)

# set external variables for usage in CMakeLists.txt
if(TENSORFLOW_FOUND)
  set(TensorFlow_LIBRARIES ${TensorFlowCC_LIBRARY} ${TensorFlowFW_LIBRARY})
  set(TensorFlow_INCLUDE_DIRS ${TensorFlow_INCLUDE_DIR})
endif()

# hide locals from GUI
mark_as_advanced(TensorFlow_INCLUDE_DIR TensorFlow_LIBRARY)
