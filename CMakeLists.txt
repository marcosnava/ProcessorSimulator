cmake_minimum_required(VERSION 3.25)
project(ProcessorSimulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProcessorSimulator main.cpp BaseComponent.cpp BaseComponent.h TestingComponent.cpp TestingComponent.h ComponentContainer.cpp ComponentContainer.h AnotherComponent.cpp AnotherComponent.h)
