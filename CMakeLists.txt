cmake_minimum_required(VERSION 3.24)
project(GameConsolOS VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(console_ui
    src/console_ui/Application.cpp
    src/console_ui/Animation.cpp
    src/console_ui/Input.cpp
    src/console_ui/Renderer.cpp
    src/console_ui/Theme.cpp
    src/console_ui/XmbShell.cpp
)

target_include_directories(console_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(console_ui PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(console_ui PRIVATE /W4 /permissive-)
else()
    target_compile_options(console_ui PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(game_consol_demo src/main.cpp)
target_link_libraries(game_consol_demo PRIVATE console_ui)

enable_testing()
add_executable(console_ui_tests tests/cpp/test_ui.cpp)
target_link_libraries(console_ui_tests PRIVATE console_ui)
add_test(NAME console_ui_tests COMMAND console_ui_tests)
