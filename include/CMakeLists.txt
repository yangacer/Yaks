
#set ( headers record.hpp rschema.hpp variantType.hpp vfactory.hpp )

install(DIRECTORY yaks/ DESTINATION include/yaks
                 FILES_MATCHING PATTERN "*.hpp")

