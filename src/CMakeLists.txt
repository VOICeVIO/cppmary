AUX_SOURCE_DIRECTORY(./common/ SRC_COMMON)
AUX_SOURCE_DIRECTORY(./modules/ SRC_MODULES)
add_library(cppmary cppmary.cpp ${SRC_COMMON} ${SRC_MODULES})
target_link_libraries(cppmary HTSEngine PugiXml)