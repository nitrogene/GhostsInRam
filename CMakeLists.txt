cmake_minimum_required(VERSION 3.16)
project(GhostsInRam VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.6 REQUIRED COMPONENTS Widgets Multimedia Core Gui)

# Définir les composants Qt nécessaires pour Core
set(CORE_QT_LIBS
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

file(GLOB_RECURSE CORE_SOURCES
    "Core/*.cpp"
    "Core/*.h"
)

add_library(Core STATIC ${CORE_SOURCES})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_link_libraries(Core PUBLIC ${CORE_QT_LIBS})
target_compile_definitions(Core PUBLIC QT_MESSAGELOGCONTEXT)

add_executable(GhostsInRam main.cpp)

target_link_libraries(GhostsInRam
    PRIVATE
    Core
    Qt6::Multimedia
    ${CORE_QT_LIBS}
)

target_compile_definitions(GhostsInRam PRIVATE QT_MESSAGELOGCONTEXT)