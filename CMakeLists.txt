cmake_minimum_required(VERSION 3.0)

project(thread_pool)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   #$变量名：取值

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)