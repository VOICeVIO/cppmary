MACRO(add_example name)
    ADD_EXECUTABLE(${name} ${name}.cpp)
    TARGET_LINK_LIBRARIES(${name} cppmary )
ENDMACRO()

add_example(jieba_test)
add_example(pugi_test)

add_executable(htsengine_test hts_engine.c)
target_link_libraries(htsengine_test cppmary)

add_example(pinyin_utf8_test)
add_example(module_test)

add_subdirectory(unittest)

#install (TARGETS htsengine_test DESTINATION ${CMAKE_BINARY_DIR}/bin)