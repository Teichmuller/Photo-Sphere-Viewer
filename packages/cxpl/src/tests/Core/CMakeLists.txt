



set(test_names "")
list(APPEND test_names ErrorHandler)
list(APPEND test_names DependentVar)
list(APPEND test_names DependentVar1)
list(APPEND test_names DynamicLoader)
add_library(testDynamicLoaderLib1 SHARED DynamicLoader_lib1.cpp)
add_library(testDynamicLoaderLib2 SHARED DynamicLoader_lib2.cpp)
# add more test files (without suffix) over here

foreach(name ${test_names})
	# add_library(${name} OBJECT ${name}.cpp)
    add_executable(${name} ${name}.cpp)
endforeach()

