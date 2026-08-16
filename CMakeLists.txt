cmake_minimum_required(VERSION 3.25)

# Fix CMake CMP0169 / policy compatibility for legacy subdependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

project(AutoDemon VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If GEODE_SDK is set, append it to CMAKE_PREFIX_PATH so find_package finds Geode
if(DEFINED GEODE_SDK)
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}")
elseif(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOURCES
        src/main.cpp
)
