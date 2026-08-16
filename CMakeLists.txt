cmake_minimum_required(VERSION 3.25)

# Fix CMP0169 policy error for legacy subdependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

# Read GEODE_SDK from environment and inject it into CMake module paths
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
    set(Geode_DIR "$ENV{GEODE_SDK}" CACHE PATH "" FORCE)
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
