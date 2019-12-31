cmake_minimum_required(VERSION 3.10)

# set project name
project(idfa VERSION 5.0 LANGUAGES CXX)

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

# define an option 
# -DUSE_MYMATH=1/0/on/off/ON/OFF
option(USE_MYMATH "Use idfa provided math implementation" ON)

# use a bool option
if(USE_MYMATH)
    # add a subdirectory to build
    add_subdirectory(MathFunctions)
    # append MathFunctions in EXTRA_LIBS    
    # list(APPEND EXTRA_LIBS MathFunctions)
endif()

# copy idfa.h.in modifying its contents
configure_file(idfa.h.in ${PROJECT_SOURCE_DIR}/include/idfa.h)

add_subdirectory(src)

# include directories for idfa
target_include_directories(idfa PUBLIC
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_BINARY_DIR}/include"
                            )


# For the testing purpose
# BUILD_TESTING is set to ON default
# use -DBUILD_TESTING=OFF to disable testing                            
if(BUILD_TESTING)
    ## use enable_testing() method when not using include(CTest)
    # enable_testing()

    # add a test to be run by ctest
    add_test(NAME Runs COMMAND idfa 2)
    
    # add_test(NAME Usage COMMAND idfa)
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
    do_test(idfa 1 "3 is 1.73205")
    do_test(idfa 2 "9 is 3")
    
endif()