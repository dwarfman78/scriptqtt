cmake_minimum_required(VERSION 3.4)
project(scriptqtt)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/mosquitto/lib/cpp)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/mosquitto/lib)
include_directories(${PROJECT_SOURCE_DIR}/extlibs/ChaiScript/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm36/3.6.2/lib/llvm-3.6/bin/clang++")
#set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm36/3.6.2/lib/llvm-3.6/bin/clang")

add_definitions(-DCHAISCRIPT_NO_THREADS)
add_definitions(-DCHAISCRIPT_NO_THREADS_WARNING)

set(SOURCE_FILES main.cpp ChaiscriptMosquitto.cpp ChaiscriptMosquitto.hpp)


link_directories(${PROJECT_SOURCE_DIR}/extlibs/mosquitto/lib/cpp)

add_executable(scriptqtt ${SOURCE_FILES})

target_link_libraries(scriptqtt mosquittopp)

target_link_libraries(scriptqtt dl)