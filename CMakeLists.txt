cmake_minimum_required(VERSION 3.10)

project(semver
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE})

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------

# Common

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Catch2

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2/single_include)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# -----------------------------------------------------------------------------

set(APP_SOURCES
  
)

set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test/version.test.cpp
)

add_executable(semver-test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/main.test.cpp
  ${APP_SOURCES}
  ${TEST_SOURCES}
)
target_link_libraries(semver-test
	${APP_LIBRARIES}
	Catch
)
