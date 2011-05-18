
include_directories( /usr/local/include 
	${PROJECT_SOURCE_DIR}/include )

option (BUILD_SHARED_LIB "Build shared library" OFF)
if(BUILD_SHARED_LIB)
	set( LIB_TYPE SHARED)
	add_definitions ( -DYAKS_MAKE_DLL )
else()
	set( LIB_TYPE STATIC)
	add_definitions ( -DYAKS_STATIC )
	
endif()

add_library(yaks ${LIB_TYPE} vfactory.cpp record.cpp rschema.cpp strref.cpp rscope.cpp)

install (TARGETS yaks LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
