AUX_SOURCE_DIRECTORY(./common/ SRC_COMMON)
AUX_SOURCE_DIRECTORY(./modules/ SRC_MODULES)
AUX_SOURCE_DIRECTORY(./features/ SRC_FEATURES)
add_library(cppmary cppmary.cpp ${SRC_COMMON} ${SRC_MODULES} ${SRC_FEATURES})
target_link_libraries(cppmary HTSEngine PugiXml)


#add_library(cppmary cppmary.cpp cppmaryAll.cpp)
#target_link_libraries(cppmary HTSEngine PugiXml)
