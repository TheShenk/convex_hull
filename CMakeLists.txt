cmake_minimum_required(VERSION 3.22)
project(convex_hull)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(LINKER_FLAGS -static -static-libstdc++ -static-libgcc)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(convex_hull
        src/main.cpp
        src/window.h
        src/convex_hull.h
        src/convex_hull.cpp)
target_link_libraries(convex_hull
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(convex_hull_test src/test.cpp src/convex_hull.h src/convex_hull.cpp)
target_link_libraries(convex_hull_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(convex_hull_test)