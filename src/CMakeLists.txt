# include directories for the sources of this directory
include_directories("${PROJECT_SOURCE_DIR}/include"
                    
                    "${PROJECT_BINARY_DIR}/include"
                    )

# build executable analyzer using sources files
add_library(analyzer 
                FlowSet.cpp
                IterableList.cpp)
