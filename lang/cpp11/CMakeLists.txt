
cmake_minimum_required(VERSION 3.3)
cmake_policy(SET CMP0042 NEW) # MACOSX_RPATH

set (CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)

project(labcpp11)

set(SOURCE_FILES
    lang.hpp
    #source_files
    lambda.cpp
    utilities.cpp
    decl.cpp
    main.cpp
)


add_executable(labcpp11 ${SOURCE_FILES})

set_property(TARGET labcpp11 PROPERTY CXX_STANDARD 11) # fails silently
target_compile_features(labcpp11 PRIVATE cxx_range_for cxx_variadic_templates) # required

#add_test(labcpp11 labcpp11)
