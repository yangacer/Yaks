
include_directories( /usr/local/include 
	${PROJECT_SOURCE_DIR}/include )

add_library(yaks vfactory.cpp record.cpp rschema.cpp strref.cpp)

install (TARGETS yaks LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
