include_directories("${PROJECT_SOURCE_DIR}/src"
                    "${LLVM_INCLUDE_DIRS}")

execute_process(COMMAND llvm-config-9  --cxxflags
                OUTPUT_VARIABLE CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config-9  --ldflags
                OUTPUT_VARIABLE LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config-9  --libs
                OUTPUT_VARIABLE LD_FLAGS1 OUTPUT_STRIP_TRAILING_WHITESPACE)
string(APPEND LD_FLAGS " ${LD_FLAGS1}")

add_executable(LA
            la.cpp)

set_property(TARGET LA 
            PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET LA 
            PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/liveness_analysis")
target_link_libraries(LA ${LD_FLAGS})
set_target_properties(LA PROPERTIES COMPILE_FLAGS ${CXX_FLAGS})
