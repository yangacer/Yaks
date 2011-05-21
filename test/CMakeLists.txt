
if(WIN32)
	include_directories( D:/contrib/include
		${PROJECT_SOURCE_DIR}/include )
elseif(UNIX)
	include_directories( /usr/local/include
		${PROJECT_SOURCE_DIR}/include )
endif()

link_directories( ${PROJECT_BINARY_DIR}/src )

option(LINK_WITH_SHARED_LIB "Link tests with shared libyaks" ON)

if(LINK_WITH_SHARED_LIB)
	add_definitions(-DYAKS_DLL)
endif()

set(TESTS record scope)
foreach(tg ${TESTS})
	add_executable(${tg} ${tg}.cpp)
	target_link_libraries(${tg} yaks)
endforeach(tg)

