# CMake build script for building an executable application.
#
# Building from source:
# > cmake . -Bbuild -DLIBDIR:STRING=<library directory>
# > cmake --build .

cmake_minimum_required(VERSION 3.5)
project(alc)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
enable_testing()

# Add header directory to project
include_directories(include)

# Add a submodule to the project
include_directories(lib/termcolor)

# Add an external library to the project
# find_package(LIB REQUIRED)
# include_directories(${LIB_INCLUDE_DIRS})

include(CMakeDependentOption)

cmake_dependent_option(USE_EXTENDED_DOUBLE_PRECISION "Use 80 bit double (long double) instead of 64 bit double." ON "NOT USE_BOOST_RATIONAL" OFF)
cmake_dependent_option(USE_BOOST_RATIONAL "Use Boost multiprecision instead of 64 bit double." OFF "NOT USE_EXTENDED_DOUBLE_PRECISION" OFF)

option(USE_LAGRANGE_WEIGHTS_TABLE "Generate a table of Lagrange weights for polynomial integration." ON)
set(MAX_LAGRANGE_POINTS "20" CACHE STRING "The maximum number integration points for which to generate Lagrange weights."  )

# Declare source files for build
set(
    SOURCE_FILES
    src/Matrix.cpp
    src/LinearAlgebra.cpp
    src/Integration.cpp
    src/Generators.cpp
)

set(
    TEST_SOURCES
    test/Matrix.cpp
    test/LinearAlgebra.cpp
    test/Integration.cpp
)

set(
    HEADER_FILES
    include/main.hpp
)

add_executable(LagrangeGenerator src/LagrangeGenerator.cpp src/Generators.cpp src/Matrix.cpp src/LinearAlgebra.cpp)

add_custom_command(
  OUTPUT lagrange_weights.cpp
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND LagrangeGenerator ${MAX_LAGRANGE_POINTS} -f ${CMAKE_BINARY_DIR}/lagrange_weights.cpp
  DEPENDS LagrangeGenerator build/CMakeCache.txt
)

add_library(lagrange_weights_generated OBJECT lagrange_weights.cpp)

# Set the name of the built executable
set(EXE_NAME "${PROJECT_NAME}")


add_executable(${EXE_NAME} src/main.cpp ${SOURCE_FILES})
set_target_properties(
    ${EXE_NAME} PROPERTIES
    VERSION 0
)

target_include_directories(${EXE_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(lib/googletest)

add_executable(Tests ${TEST_SOURCES} ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)

if(USE_LAGRANGE_WEIGHTS_TABLE)
  target_sources( Tests PRIVATE $<TARGET_OBJECTS:lagrange_weights_generated> )
  target_sources( ${EXE_NAME} PUBLIC $<TARGET_OBJECTS:lagrange_weights_generated> )
  add_definitions ( /DUSE_LAGRANGE_WEIGHTS_TABLE )
endif()

if(USE_EXTENDED_DOUBLE_PRECISION)
  add_definitions( /DUSE_EXTENDED_DOUBLE_PRECISION )
elseif(USE_BOOST_RATIONAL)
  find_package(Boost REQUIRED COMPONENTS multiprecision)
  include_directories( ${Boost_INCLUDE_DIRS} )
  add_definitions( /DUSE_BOOST_RATIONAL )
endif()