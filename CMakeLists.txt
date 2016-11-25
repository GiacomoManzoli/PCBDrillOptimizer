cmake_minimum_required(VERSION 3.6)
project(Parte_2___Meta_eurstiche)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

set(SOURCE_FILES main.cpp common/Solution.cpp common/Solution.h ga/Population.cpp ga/Population.h common/Problem.cpp common/Problem.h ga/GASolver.cpp ga/GASolver.h cplex/cpxmacro.h cplex/CPLEXSolver.cpp cplex/CPLEXSolver.h)

FIND_PACKAGE(CPLEX REQUIRED)

INCLUDE_DIRECTORIES(include ${CPLEX_INCLUDE_DIR})

add_executable(Parte_2___Meta_eurstiche ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Parte_2___Meta_eurstiche  ${CPLEX_LIBRARIES})
