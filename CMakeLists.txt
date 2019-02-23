cmake_minimum_required(VERSION 3.0)


project(proceesing)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(
     sample
     main.cpp  
     processing/imageprocessing.cpp  
   )