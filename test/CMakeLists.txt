include_directories( d:/contrib/include ${PROJECT_SOURCE_DIR}/include )
link_directories( ${PROJECT_BINARY_DIR}/src )
add_definitions( -DYAKS_DLL )
set(TESTS record scope factory)
foreach(tg ${TESTS})
	add_executable(${tg} ${tg}.cpp)
	target_link_libraries(${tg} yaks)
endforeach(tg)

