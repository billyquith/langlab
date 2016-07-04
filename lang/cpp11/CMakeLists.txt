
cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0042 NEW) # MACOSX_RPATH

set(SOURCE_FILES    
    #source_files
    main.cpp
)
    
set_property(TARGET ponder PROPERTY CXX_STANDARD 11) # fails silently
target_compile_features(labcpp11 PUBLIC cxx_range_for cxx_variadic_templates) # required

add_executable(labcpp11 ${SOURCE_FILES})

add_test(labcpp11 labcpp11)
