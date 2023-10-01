cmake_minimum_required(VERSION 3.26)
project(CopyFinderV2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

add_executable(CopyFinderV2 main.cpp)
target_link_libraries(CopyFinderV2
        Qt5::Core
)

