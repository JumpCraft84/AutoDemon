cmake_minimum_required(VERSION 3.25)

# 1. Fix policy requirements for FetchContent / TulipHook subdependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

# 2. Tell CMake where to find Geode BEFORE project() initialization
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
    set(Geode_DIR "$ENV{GEODE_SDK}" CACHE PATH "")
endif()

project(AutoDemon VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Locate Geode package configuration
find_package(Geode REQUIRED)

# 4. Target definition
add_geode_mod(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOURCES
        src/main.cpp
)
