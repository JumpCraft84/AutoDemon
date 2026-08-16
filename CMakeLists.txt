cmake_minimum_required(VERSION 3.25)

# Allow legacy subdependencies to compile under newer CMake versions
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

# Setup Geode SDK path if provided by environment
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

project(AutoDemon VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geode REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOURCES
        src/main.cpp
)
