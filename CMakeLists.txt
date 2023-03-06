cmake_minimum_required(VERSION 3.24)
project(B_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(BP_Tree src/main.cpp src/block.cpp src/record.cpp src/tree_node.cpp src/b_plus_tree.cpp src/disk.cpp)
