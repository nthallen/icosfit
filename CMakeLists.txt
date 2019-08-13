cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(icosfit VERSION 4.0.0)

set(BUILD_DEMO FALSE CACHE BOOL "Build demo program?")
add_subdirectory(levmar-2.6)
add_subdirectory(icosfit/cppsrc)
