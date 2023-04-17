cmake_minimum_required(VERSION 3.24)
project(lab2)
set(CMAKE_CXX_STANDARD 11)
add_executable(lab2 Stack.h Stack.cpp StackImplementation.h main.cpp VectorStack.cpp VectorStack.h Vector.h Vector.cpp ListStack.cpp ListStack.h)
