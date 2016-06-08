INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/gtest/include)

ADD_EXECUTABLE(test.run
        gtest_main.cpp
        jieba_test.cpp
		unicode_test.cpp
)

if(MSVC)
	TARGET_LINK_LIBRARIES(test.run gtest)
else()
	TARGET_LINK_LIBRARIES(test.run gtest pthread)
endif()
