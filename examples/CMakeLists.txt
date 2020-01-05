add_executable(t1 
            t1.cpp)

set_target_properties(t1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")