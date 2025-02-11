cmake_minimum_required(VERSION 3.16)
project(RT_Testing_Week1
  VERSION 0.0.1
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)
enable_testing() 

file(GLOB SOURCE_FILES ../source/*.cpp)
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
add_executable(TestWeek1 ${SOURCE_FILES} testWeek1.cpp)
target_include_directories(TestWeek1 PUBLIC ${CMAKE_SOURCE_DIR}/../include/)
target_link_libraries(TestWeek1 PUBLIC Catch2::Catch2WithMain)

add_test(NAME TestWeek1 COMMAND TestWeek1)