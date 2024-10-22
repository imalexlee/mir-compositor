cmake_minimum_required(VERSION 3.29)
project(mir_compositor)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MIRAL miral REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
        src/shell_manager.cpp
        src/shell_manager.h)

target_include_directories(${PROJECT_NAME} PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MIRAL_LDFLAGS})

add_executable(TEST test/tests.cpp src/shell_manager.cpp src/shell_manager.h)

target_include_directories(TEST PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS})
target_link_libraries(TEST ${MIRAL_LDFLAGS})
