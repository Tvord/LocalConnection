project(localsocket)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH /usr/lib64/)
include_directories (${CMAKE_BINARY_DIR})
link_directories(${CMAKE_SOURCE_DIR}../../lib)

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /usr/lib64/qt4/)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 4.8.7 REQUIRED QtCore QtNetwork )

set(SOURCES  main.cpp )
#set(HEADERS main.cpp)

add_executable(localsocket ${SOURCES})# ${HEADERS})
target_link_libraries(localsocket Qt4::QtCore Qt4::QtNetwork consolereader localconnection)