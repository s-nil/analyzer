# include directories for the sources of this directory
include_directories("${PROJECT_SOURCE_DIR}/include"
                    
                    "${PROJECT_BINARY_DIR}/include"
                    )
include_directories(${CMAKE_SOURCE_DIR}/MathFunctions/include)

# build executable analyzer using sources files
add_executable(analyzer 
                analyzer.cpp)
