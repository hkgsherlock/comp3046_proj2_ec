cmake_minimum_required(VERSION 2.6)
project(COMP3046_PROJECT_2_ec)

set(CMAKE_C_STANDARD 11)

find_package(OPENMP)
IF(OPENMP_FOUND)
    MESSAGE(STATUS "OpenMP found, adding flags for compilers and linkers")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPENMP_C_FLAGS}")
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OPENMP_EXE_LINKER_FLAGS}")
ELSE()
    MESSAGE(FATAL_ERROR "missing OpenMP")
ENDIF()

# custom flags for linker-OpenMP flags (GCC-specific)
MESSAGE(STATUS "custom flags for linker-OpenMP flags (GCC-specific)")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
SET(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -lgomp")
SET(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -lgomp")

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(SOURCE_FILES ${SOURCE_FILES}
        src/matrix.c
        src/vector.c
        src/gaussian.c
        src/gaussian_validate.c
        src/gaussian_omp.c
        src/main.c)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(gaussian ${SOURCE_FILES})
