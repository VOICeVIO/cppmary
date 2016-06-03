
MACRO(add_example name)
    ADD_EXECUTABLE(${name} ${name}.cpp)
    TARGET_LINK_LIBRARIES(${name} cppmary )
ENDMACRO()

add_example(libtest)