cmake_minimum_required(VERSION 3.26)
project(HashTable)

set(CMAKE_CXX_STANDARD 23)

add_executable(HashTable main.cpp
        DynamicArray.h
        LinkedList.h)
