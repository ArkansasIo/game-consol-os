cmake_minimum_required(VERSION 3.24)
project(GameConsolOS VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL examples" FORCE)
set(SDLTTF_VENDORED ON CACHE BOOL "Build SDL_ttf dependencies" FORCE)
set(SDLTTF_SAMPLES OFF CACHE BOOL "Disable SDL_ttf samples" FORCE)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.18
    GIT_SHALLOW TRUE)
FetchContent_Declare(SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL3 SDL3_ttf)

add_library(console_ui
    src/console_ui/Application.cpp
    src/console_ui/Animation.cpp
    src/console_ui/Input.cpp
    src/console_ui/Renderer.cpp
    src/console_ui/Theme.cpp
    src/console_ui/XmbShell.cpp)
target_include_directories(console_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(console_ui PUBLIC cxx_std_23)

add_library(gameos_core
    src/gameos/core/Kernel.cpp
    src/gameos/core/EventBus.cpp
    src/gameos/core/ProcessManager.cpp
    src/gameos/core/VirtualFileSystem.cpp
    src/gameos/core/Logger.cpp
    src/gameos/core/ConfigStore.cpp)
target_include_directories(gameos_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(gameos_core PUBLIC cxx_std_23)

add_library(gameos_update src/gameos/update/UpdateManager.cpp)
target_include_directories(gameos_update PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(gameos_update PUBLIC cxx_std_23)

add_library(gameos_gui
    src/gameos/gui/Gui.cpp
    src/gameos/gui/WindowManager.cpp)
target_include_directories(gameos_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(gameos_gui PUBLIC cxx_std_23)

add_library(gameos_desktop
    src/gameos/platform/DesktopApp.cpp
    src/gameos/platform/DesktopRenderer.cpp)
target_include_directories(gameos_desktop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(gameos_desktop PUBLIC
    console_ui gameos_core gameos_update gameos_gui SDL3::SDL3 SDL3_ttf::SDL3_ttf)
target_compile_features(gameos_desktop PUBLIC cxx_std_23)

if(MSVC)
    foreach(t console_ui gameos_core gameos_update gameos_gui gameos_desktop)
        target_compile_options(${t} PRIVATE /W4 /permissive-)
    endforeach()
else()
    foreach(t console_ui gameos_core gameos_update gameos_gui gameos_desktop)
        target_compile_options(${t} PRIVATE -Wall -Wextra -Wpedantic)
    endforeach()
endif()

add_executable(game_consol_demo src/main.cpp)
target_link_libraries(game_consol_demo PRIVATE gameos_desktop)

if(WIN32)
    set_target_properties(game_consol_demo PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_target_properties(game_consol_demo PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.arkansasio.gameconsolos"
        MACOSX_BUNDLE_BUNDLE_NAME "GameConsolOS")
endif()

enable_testing()
add_executable(console_ui_tests tests/cpp/test_ui.cpp)
target_link_libraries(console_ui_tests PRIVATE console_ui)
add_executable(gameos_core_tests tests/cpp/test_core.cpp)
target_link_libraries(gameos_core_tests PRIVATE gameos_core gameos_update gameos_gui)
add_test(NAME console_ui_tests COMMAND console_ui_tests)
add_test(NAME gameos_core_tests COMMAND gameos_core_tests)

install(TARGETS game_consol_demo RUNTIME DESTINATION bin BUNDLE DESTINATION .)
set(CPACK_PACKAGE_NAME "GameConsolOS")
set(CPACK_PACKAGE_VENDOR "ArkansasIo")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++23 console-style desktop OS shell")
if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ")
endif()
include(CPack)
