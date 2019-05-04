cmake_minimum_required(VERSION 3.1)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BUILD_DIR}" IS_IN_SOURCE_BUILD)
if(IS_IN_SOURCE_BUILD)
    message(FATAL_ERROR "You are building in-source. This is NOT allowed!")
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql Xml)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(SOURCES
    main.cpp
    PanharmoniconWindow.cpp
    PanharmoniconWindow.h
    PanharmoniconWindow.ui

    DeckEditorWidget.cpp
    DeckEditorWidget.h
    DeckEditorWidget.ui
)
add_executable(panharmonicon  ${SOURCES})
target_link_libraries(panharmonicon Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql Qt5::Xml)

