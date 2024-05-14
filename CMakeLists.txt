cmake_minimum_required(VERSION 3.10)

project(Snake VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED Widgets Multimedia)

#file(GLOB SNAKE_SOURCES_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.CPP)

#file(GLOB SNAKE_CLIENT_SOURCES_H ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#add_executable(${PROJECT_NAME} ${SNAKE_CLIENT_SOURCES_CPP} ${SNAKE_CLIENT_SOURCES_H})

set(PROJECT_SOURCES 
	main.cpp
	MainWindow.h
	MainWindow.cpp
	PlayWindow.h
	PlayWindow.cpp
	Snake.h
	Snake.cpp
	Resource.qrc
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Multimedia)