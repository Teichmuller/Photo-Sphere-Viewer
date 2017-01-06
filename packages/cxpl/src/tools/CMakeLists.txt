



set(tools_names "")
list(APPEND tools_names StringEncript)
#list(APPEND tools_names PseudoDesktop)
# add more test files (without suffix) over here

foreach(name ${tools_names})
	# add_library(${name} OBJECT ${name}.cpp)
    add_executable(${name} ${name}.cpp)
endforeach()

