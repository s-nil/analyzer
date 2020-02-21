# include directories for the sources of this directory
include_directories("${PROJECT_SOURCE_DIR}/include"
                    
                    "${PROJECT_BINARY_DIR}/include"
                    )

                    
# build executable analyzer using sources files
add_library(analyzer 
                ObjectIntMapper.cpp
                AbstractBoundedFlowSet.cpp
                AbstractFlowSet.cpp
                ArrayPackedSet.cpp
                ArraySparseSet.cpp
                AbstractFlowAnalysis.cpp
                FlowAnalysis.cpp
                ForwardFlowAnalysis.cpp
                BackwardFlowAnalysis.cpp
                NodeData.cpp
                FunctionCFG.cpp
                ArrayValueUniverse.cpp)
