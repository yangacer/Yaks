include_directories( /usr/local/include ${PROJECT_SOURCE_DIR}/include )
link_directories( ${PROJECT_BINARY_DIR}/src )

add_executable(fac test_factory.cpp)
target_link_libraries(fac yaks)

add_executable(overall main.cpp)
target_link_libraries(overall yaks)
