#set(SOURCE_FILES jieba_test.cpp)
#add_executable(cppmary ${SOURCE_FILES})

MACRO(add_example name)
    ADD_EXECUTABLE(${name} ${name}.cpp)
    TARGET_LINK_LIBRARIES(${name} cppmary )
ENDMACRO()

add_example(jieba_test)

add_executable(htsengine_test hts_engine.c)
target_link_libraries(htsengine_test cppmary)

#install (TARGETS htsengine_test DESTINATION ${CMAKE_BINARY_DIR}/bin)