cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_STANDARD 11)# SET(CMAKE_CXX_COMPTLER "g++")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
SET(CMAKE_BUILE_TYPE DEBUG)
#SET(CMAKE_CXX_COMPTLER "g++")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

project(pb)

# opencv
#find_package(OpenCV REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/opencv NO_DEFAULT_PATH)
#message(STATUS ${OpenCV_LIBS})
#message(STATUS ${OpenCV_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/opencv/include) # opencv
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/tbb/include) # tbb
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/facedetect/include) # imi facedetect
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/eigen3) # eigen
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/tensorflow-1.7.0/genfiles) # tensorflow
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/tensorflow-1.7.0) # tensorflow
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/protobuf/src) # protobuf
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/nsync/public)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

# tensorflow
SET(DEP_LIB 
    ${PROJECT_SOURCE_DIR}/tensorflow-1.7.0/bazel-lib/libtensorflow_cc.so
    ${PROJECT_SOURCE_DIR}/tensorflow-1.7.0/bazel-lib/libtensorflow_framework.so
    )
# opencv
SET(OpenCV_LIB
        ${PROJECT_SOURCE_DIR}/opencv/lib/libopencv_core.so
        ${PROJECT_SOURCE_DIR}/opencv/lib/libopencv_imgproc.so
        ${PROJECT_SOURCE_DIR}/opencv/lib/libopencv_highgui.so
        ${PROJECT_SOURCE_DIR}/opencv/lib/libopencv_objdetect.so
        )
# facedetect
SET(FaceDetect_LIB ${PROJECT_SOURCE_DIR}/facedetect/lib/libfacedetect.so)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/tensorflow-1.7.0/bazel-lib)
#link_directories(/home/soon/ZF/pb_test/tensorflow-1.7.0/bazel-lib)
#link_directories(${PROJECT_SOURCE_DIR}/opencv/lib)

add_executable(pb main.cpp ZFutil.cpp)

target_link_libraries(pb ${OpenCV_LIB})
target_link_libraries(pb ${DEP_LIB})
target_link_libraries(pb ${FaceDetect_LIB})
