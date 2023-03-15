cmake_minimum_required(VERSION 3.24)
project(shotten)

set(CMAKE_CXX_STANDARD 20)
FILE(GLOB src shotten/*.cpp shotten/*.h)
ADD_EXECUTABLE(shotten ${src})