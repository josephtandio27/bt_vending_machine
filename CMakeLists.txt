
cmake_minimum_required(VERSION 3.10)
project(vm_bt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point to local BehaviorTree.CPP install
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../BehaviorTree.CPP/install")

# Find the BehaviorTree.CPP package
# find_package(BehaviorTreeCPP REQUIRED)
add_subdirectory(../BehaviorTree.CPP build)

# Create executable
add_executable(vm_bt
    src/main.cpp
    src/vm_sys.cpp
)

target_include_directories(vm_bt PRIVATE 
    src
    include
)
# Link BehaviorTree.CPP
target_link_libraries(vm_bt PRIVATE BT::behaviortree_cpp)

