AUX_SOURCE_DIRECTORY(./common/ SRC_COMMON)
AUX_SOURCE_DIRECTORY(./modules/ SRC_MODULES)
AUX_SOURCE_DIRECTORY(./features/ SRC_FEATURES)
AUX_SOURCE_DIRECTORY(./hts_engine/ SRC_HTSENGINE)
AUX_SOURCE_DIRECTORY(../3rdparty/pugixml/ SRC_PUGIXML)
add_library(cppmary cppmary.cpp ${SRC_COMMON} ${SRC_MODULES} ${SRC_FEATURES} ${SRC_HTSENGINE} ${SRC_PUGIXML})
target_link_libraries(cppmary)


#add_library(cppmary cppmary.cpp cppmaryAll.cpp)
#target_link_libraries(cppmary  PugiXml)

#add_library(cppmary cppmary.cpp cppmaryAll.cpp ../3rdparty/pugixml/pugixml.cpp)
