include_directories("${PROJECT_SOURCE_DIR}/include"
                    "${LLVM_INCLUDE_DIRS}")

add_library(pass MODULE
            pass1.cpp)

set_property(TARGET pass 
            PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET pass 
            PROPERTY LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib/test_pass")

target_link_libraries(pass analyzer)
