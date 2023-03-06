cmake_minimum_required(VERSION 3.24)
project(B_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(CZ4031_DB_Project
        src/block.cpp
        src/block.h
        src/disk.cpp
        src/disk.h
        src/main.cpp
        src/record.cpp
        src/record.h src/b_plus_tree.cpp src/b_plus_tree.h src/tree_node.cpp src/tree_node.h src/linked_list.h)
