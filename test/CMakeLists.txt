#set(SOURCE_FILES jieba_test.cpp)
#add_executable(cppmary ${SOURCE_FILES})

MACRO(add_example name)
    ADD_EXECUTABLE(${name} ${name}.cpp)
    TARGET_LINK_LIBRARIES(${name} cppmary )
ENDMACRO()

add_example(jieba_test)
