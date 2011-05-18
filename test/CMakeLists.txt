include_directories( /usr/local/include ${PROJECT_SOURCE_DIR}/include )
link_directories( ${PROJECT_BINARY_DIR}/src )

set(TESTS record factory scope gutils)
foreach(tg ${TESTS})
	add_executable(${tg} ${tg}.cpp)
	target_link_libraries(${tg} yaks)
endforeach(tg)

