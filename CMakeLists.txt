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

# Declare source files for build
set(
    SOURCE_FILES
    src/Matrix.cpp
    src/LinearAlgebra.cpp
)

set(
    HEADER_FILES
    include/main.hpp
)

# Set the name of the built executable
set(EXE_NAME "${PROJECT_NAME}")

add_executable(${EXE_NAME} src/main.cpp ${SOURCE_FILES})
set_target_properties(
    ${EXE_NAME} PROPERTIES
    VERSION 0
)

target_include_directories(${EXE_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# GTest
# Download and unpack googletest at configure time
configure_file(lib/googletest/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

add_executable(Tests test/Matrix.cpp test/LinearAlgebra.cpp ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)

# Link with an external package
# target_link_libraries(${EXE_NAME} ${LIB_LIBRARIES})

# Link with a submodule
# target_link_libraries(${EXE_NAME} ${SUBPROJECT_NAME})

# Copy dynamic libraries to executable directory if necessary
# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${LIB_SHARED_LIB}
#         $<TARGET_FILE_DIR:${PROJECT_NAME}>
# )