# include directories for the sources of this directory
include_directories("${PROJECT_SOURCE_DIR}/include"
                    
                    "${PROJECT_BINARY_DIR}/include"
                    )
include_directories(${CMAKE_SOURCE_DIR}/MathFunctions/include)

# build executable idfa using sources files
add_executable(idfa 
                idfa.cpp)

# link library MathFunctions with target executable idfa
if(USE_MYMATH)
    target_link_libraries(idfa MathFunctions)
endif()