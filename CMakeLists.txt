cmake_minimum_required(VERSION 3.10)

# set project name
project(analyzer VERSION 1.0 LANGUAGES CXX)

# For the testing purpose
# an option BUILD_TESTING is created{default is ON}
include(CTest)

# put archive target files in
# https://cmake.org/cmake/help/v3.4/manual/cmake-buildsystem.7.html#id32
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# put all runtime target files in 
# https://cmake.org/cmake/help/v3.4/manual/cmake-buildsystem.7.html#id30
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# put all the library target files in
# https://cmake.org/cmake/help/v3.4/manual/cmake-buildsystem.7.html#id31
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# required to create a shared object
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# http://llvm.org/docs/CMake.html#id15 // embedding LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM : ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVMConfig.cmake found at : ${LLVM_DIR}")
message(STATUS "LLVM headers found at : ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Binaries found at : ${LLVM_TOOLS_BINARY_DIR}")
message(STATUS "LLVM Libraries found at : ${LLVM_LIBRARY_DIR}")

message(STATUS "Using Compiler : ${CMAKE_CXX_COMPILER}")
# set(LLVM_LIBRARY_DIR "${LLVM_LIBRARY_DIR} ${CMAKE_BINARY_DIR}/lib")

# copy analyzer.h.in modifying its contents
configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

# include directories for analyzer
target_include_directories(analyzer PUBLIC
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_BINARY_DIR}/include"
		            "${PROJECT_BINARY_DIR}"
			    "${LLVM_INCLUDE_DIRS}"
                            )


# For the testing purpose
# BUILD_TESTING is set to ON default
# use -DBUILD_TESTING=OFF to disable testing                            
if(BUILD_TESTING)
    ## use enable_testing() method when not using include(CTest)
    # enable_testing()

    # add a test to be run by ctest
    add_test(NAME Runs COMMAND analyzer 2)
    
    # add_test(NAME Usage COMMAND analyzer)
    # set_tests_properties(Usage
    #     PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .*number")
    
    # create a function do_test with arguments, target and result
    function(do_test target arg result)
        
        add_test(NAME Comp${arg} COMMAND ${target})
        
        # set a property of tests {if test with this name not found -> error}
        # output must match the regex for the test to pass
        # other properties : https://cmake.org/cmake/help/v3.8/manual/cmake-properties.7.html#properties-on-tests
        set_tests_properties(Comp${arg}
            PROPERTIES PASS_REGULAR_EXPRESSION ${result})

    endfunction(do_test)
    
    # calling the test function
    do_test(analyzer 1 "3 is 1.73205")
    do_test(analyzer 2 "9 is 3")
    
endif()
