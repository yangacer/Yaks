
if(WIN32)
	include_directories( D:/contrib/include
		${PROJECT_SOURCE_DIR}/include )
elseif(UNIX)
	include_directories( /usr/local/include
		${PROJECT_SOURCE_DIR}/include )
endif()

link_directories( ${PROJECT_BINARY_DIR}/src )

set(TESTS record scope factory)

add_definitions(-DYAKS_DLL)

foreach(tg ${TESTS})
	add_executable(${tg} ${tg}.cpp)
	target_link_libraries(${tg} yaks)
endforeach(tg)

