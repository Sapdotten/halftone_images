cmake_minimum_required (VERSION 3.8)

project (Halftone CXX)
set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_library(matrix STATIC "include/matrix/matrix.h" "include/matrix/matrix.cc")
add_library(halftone STATIC "include/halftone/halftone.h" "include/halftone/halftone.cc")
target_include_directories(matrix PUBLIC "include/matrix")
target_include_directories(halftone PUBLIC "include/halftone")


# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")
target_link_libraries(halftone PRIVATE matrix)
target_link_libraries(${PROJECT_NAME} halftone)
# TODO: Add tests and install targets if needed.