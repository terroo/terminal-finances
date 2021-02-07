cmake_minimum_required(VERSION 3.5)

project(Terminal-Finances LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql PrintSupport LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql PrintSupport LinguistTools REQUIRED)

set(TS_FILES
    terminalfinances/TerminalFinances_en_US.ts
    terminalfinances/TerminalFinances_es_ES.ts
)

set (PROJECT_HEADERS
    accountslist.h
    filesave.h
    gendoc.h
    initial.h
    model.h
    start.h
    terminalfinances.h
    tools.h
    updatefields.h
    views.h
)

set(PROJECT_SOURCES
        accountslist.cpp
        filesave.cpp
        gendoc.cpp
        initial.cpp
        main.cpp
        model.cpp
        start.cpp
        terminalfinances.cpp
        tools.cpp
        updatefields.cpp
        views.cpp
        terminalfinances.ui
        updatefields.ui
        ${PROJECT_HEADERS}
        ${TS_FILES}
)

set(ASSETS_RESOURCES assets/images.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Terminal-Finances
        ${PROJECT_SOURCES}
        ${ASSETS_RESOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(Terminal-Finances
        ${PROJECT_SOURCES}
        ${ASSETS_RESOURCES}
    )

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Terminal-Finances PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::PrintSupport
)

install()
