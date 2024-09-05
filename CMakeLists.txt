cmake_minimum_required(VERSION 3.23)

option(USE_CODE_VIRTUALIZER "Use CodeVirtualizer macro for protection" ON)


project(navel)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}")


add_subdirectory(extlibs)
add_subdirectory(source)

add_library(navel MODULE source/main.cpp)

target_compile_definitions(navel PRIVATE WIN32_LEAN_AND_MEAN)

find_library(REQUIRED cv-sdk)


if(USE_CODE_VIRTUALIZER)
    target_compile_definitions(navel PRIVATE USE_CODE_VIRTUALIZER)
    target_link_libraries(navel PRIVATE cv-sdk)
endif ()

target_link_libraries(navel PRIVATE omath nlohmann_json)