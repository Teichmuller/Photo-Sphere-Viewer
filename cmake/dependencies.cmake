# These list variables are going to be sent to caller
set(Dependencies_BINS "")
set(Dependencies_INCLUDE_DIRS "")
set(Dependencies_LIBRARIES "")
set(Dependencies_LIBRARY_DIRS "")
set(Dependencies_DEFINITIONS "")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
# Set up Dependencies variables
if (NOT MSVC)
	find_package(Exiv2 REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${EXIV2_INCLUDE_DIR})
	list(APPEND Dependencies_LIBRARIES PUBLIC ${EXIV2_LIBRARIES})
	list(APPEND Dependencies_DEFINITIONS PUBLIC ${EXIV2_DEFINITIONS})
	
	find_package(OpenGL REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${OPENGL_INCLUDE_DIR})
	list(APPEND Dependencies_LIBRARIES PUBLIC ${OPENGL_LIBRARIES})
	
	find_package(GLEW REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${GLEW_INCLUDE_DIR})
	list(APPEND Dependencies_LIBRARIES PUBLIC ${GLEW_LIBRARIES})

	find_package(FreeGLUT REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${FREEGLUT_INCLUDE_DIRS})
	list(APPEND Dependencies_LIBRARIES PUBLIC ${FREEGLUT_LIBRARIES})

	find_package(FreeImage REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${FreeImage_INCLUDE_DIRS})
	list(APPEND Dependencies_LIBRARIES PUBLIC ${FreeImage_LIBRARIES})
	list(APPEND Dependencies_LIBRARY_DIRS PUBLIC ${FreeImage_LIBRARY_DIRS})

	find_package(GLM REQUIRED)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${GLM_INCLUDE_DIRS})
else()
	list(APPEND Dependencies_BINS PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/bin)
	list(APPEND Dependencies_INCLUDE_DIRS PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/include)
	list(APPEND Dependencies_LIBRARY_DIRS PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/lib)
	list(APPEND Dependencies_LIBRARIES PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/lib/FreeImage.lib)
	list(APPEND Dependencies_LIBRARIES PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/lib/exiv2.lib)
	
	# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		# ${CMAKE_SOURCE_DIR}/ThirdParty/packages.config
		# ${CMAKE_CURRENT_BINARY_DIR}
		# )
	# add_custom_command(TARGET ${PROJECT_NAME}
		# PRE_BUILD
		# COMMAND nuget restore ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.sln
	# )
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/ThirdParty/packages.config
		${CMAKE_CURRENT_BINARY_DIR}
		)
	execute_process(COMMAND nuget restore ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.sln)
endif()
