aux_source_directory(. SRC_LIST)
aux_source_directory(./test SRC_TEST_LIST)
add_executable(ThreadPool ${SRC_LIST})
add_executable(Test ${SRC_TEST_LIST})