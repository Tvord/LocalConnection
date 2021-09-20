project(consolereader)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH /usr/lib64/)
include_directories (${CMAKE_BINARY_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /usr/lib64/qt4/)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../lib)
find_package(Qt4 4.8.7 REQUIRED QtCore )

set(SOURCES ConsoleReader.cpp ConsoleReader.h)
#set(HEADERS main.cpp)

add_library(consolereader STATIC ${SOURCES})# ${HEADERS})
target_link_libraries(consolereader Qt4::QtCore )