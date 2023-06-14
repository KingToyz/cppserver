cmake_minimum_required(VERSION 3.20)
# include(FetchContent)
project(testmainepollagent)
set (CMAKE_CXX_FLAGS "-Werror")
add_subdirectory(jsoncpp)
include_directories(jsoncpp/include)
add_library(jsoncpp STATIC jsoncpp/src/lib_json/json_reader.cpp jsoncpp/src/lib_json/json_value.cpp jsoncpp/src/lib_json/json_writer.cpp)

link_directories(/usr/local/lib/)
# FetchContent_Declare(llhttp
#   URL "https://github.com/nodejs/llhttp/archive/refs/tags/release/v8.1.0.tar.gz")

# set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
# set(BUILD_STATIC_LIBS ON CACHE INTERNAL "")
# FetchContent_MakeAvailable(llhttp)
add_executable(testmainepollagent testmainepollagent.cpp mainepollagent.cpp subepollagent.cpp epoll.cpp connection.cpp context.cpp parse.cpp)   

# Link with the llhttp_static target
target_link_libraries(testmainepollagent pthread libhttp_parser.so)