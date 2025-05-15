cmake_minimum_required(VERSION 3.30)
project(DA_Project_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_SOURCE_DIR}/Reader
        ${CMAKE_SOURCE_DIR}/DataTypes
)

add_executable(DA_Project_2
        main.cpp
        menu.cpp
        exercises.cpp
        Reader/Reader.cpp
        DataTypes/pallet.cpp
        DataTypes/truck.cpp
)

