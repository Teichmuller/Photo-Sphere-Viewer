


set(gl_external_libs "")
list(APPEND gl_external_libs opengl32)
list(APPEND gl_external_libs freeglut)
list(APPEND gl_external_libs glew32)

set(test_names "")
list(APPEND test_names Julia)
# add more test files (without suffix) over here

foreach(name ${test_names})
	# add_library(${name} OBJECT ${name}.cpp)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${gl_external_libs})
endforeach()

