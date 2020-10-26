cmake_minimum_required(VERSION 3.17)
project(CppMake_LibMySQL)
set(CMAKE_CXX_STANDARD 14)

include(conan/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(CppMake_LibMySQL main.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})