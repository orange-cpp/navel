cmake_minimum_required(VERSION 3.23)

option(USE_CODE_VIRTUALIZER "Use CodeVirtualizer macro for protection" ON)

include(cmake/vcpkg.cmake)


project(navel)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}")


add_subdirectory(external)
add_subdirectory(source)

add_library(navel MODULE source/main.cpp)

target_compile_definitions(navel PRIVATE WIN32_LEAN_AND_MEAN)

find_library(REQUIRED cv-sdk)

vcpkg_install_if_not_found(nlohmann-json)
vcpkg_install_if_not_found(minhook)

if(USE_CODE_VIRTUALIZER)
    target_compile_definitions(navel PRIVATE USE_CODE_VIRTUALIZER)
    target_link_libraries(navel PRIVATE cv-sdk)
endif ()