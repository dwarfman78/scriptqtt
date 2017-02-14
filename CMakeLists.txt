cmake_minimum_required(VERSION 3.4)
project(scriptqtt)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/paho/src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)


link_directories(${PROJECT_SOURCE_DIR}/extlibs/paho/src)

add_executable(scriptqtt ${SOURCE_FILES})

target_link_libraries(scriptqtt paho)