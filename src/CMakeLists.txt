#add_library(cppmary cppmary.cpp)
AUX_SOURCE_DIRECTORY(./common/ SRC_LIST1)
add_library(cppmary cppmary.cpp common/util.cpp common/convertPinyin.cpp modules/TextToMaryXml.cpp ../include/modules/TextToMaryXml.h)
target_link_libraries(cppmary HTSEngine PugiXml)