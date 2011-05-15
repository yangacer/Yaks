cmake_minimum_required (VERSION 2.8)

include_directories( /usr/local/include )

add_library(yaks vfactory.cpp record.cpp rschema.cpp strref.cpp)

add_executable(fac test_factory.cpp)
target_link_libraries(fac yaks)

add_executable(overall main.cpp)
target_link_libraries(overall yaks)
