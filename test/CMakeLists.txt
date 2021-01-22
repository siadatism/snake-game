cmake_minimum_required(VERSION 2.6)

project(snake-game-test)

enable_testing()
include_directories(../src)

file(GLOB_RECURSE TEST_FILES FOLLOW_SYMLINKS "*.cpp")

foreach(TEST_FILE ${TEST_FILES})
	
	get_filename_component(TEST_FILE_PURE ${TEST_FILE} NAME_WE)
	set(TEST_NAME "${TEST_FILE_PURE}-test")
	add_executable(${TEST_NAME} ${TEST_FILE})

	target_link_libraries(${TEST_NAME} snake-lib snake-lib)
	target_link_libraries(${TEST_NAME} gtest gtest_main pthread)
	add_test(${TEST_NAME} ${TEST_FILE})
endforeach()
