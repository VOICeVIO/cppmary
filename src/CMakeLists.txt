#add_library(cppmary cppmary.cpp)
AUX_SOURCE_DIRECTORY(./common/ SRC_LIST1)
add_library(cppmary cppmary.cpp common/stringUtil.cpp)
target_link_libraries(cppmary HTSEngine PugiXml)