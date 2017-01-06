
#add_subdirectory(cxpl)

if (cxpl_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (cxpl_BUILD_TOOLS)
    add_subdirectory(tools)
endif()
