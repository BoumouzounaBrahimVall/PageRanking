cmake_minimum_required(VERSION 3.24)
project(PageRanking)

set(CMAKE_CXX_STANDARD 17)


set(Boost_INCLUDE_DIR C:/local/boost_1_81_0)
set(Boost_LIBRARY_DIR C:/local/boost_1_81_0/stage/lib)

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})


add_executable(PageRanking boot.cpp)
