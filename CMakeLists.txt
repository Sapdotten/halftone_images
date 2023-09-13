cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)
project (HalftoneImages)

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")

# TODO: Add tests and install targets if needed.