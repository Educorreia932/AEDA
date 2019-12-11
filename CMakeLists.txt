cmake_minimum_required(VERSION 3.15)
project(SUP_School)

set(CMAKE_CXX_STANDARD 17)

add_executable(SUP_School Source/Main.cpp Headers/School.h Headers/Client.h Headers/Activity.h Headers/Material.h Headers/Teacher.h Source/School.cpp Source/Teacher.cpp Source/Material.cpp Source/Client.cpp Source/Time.cpp Source/Menu.cpp Headers/Menu.h Source/Activity.cpp Source/Auxiliary.cpp Headers/Auxiliary.h Headers/Schedule.h Source/Schedule.cpp Headers/BST.h)

