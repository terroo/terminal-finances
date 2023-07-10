cmake_minimum_required(VERSION 3.5)

project(TerminalFinances VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(include_directories src)

set(PROJECT_SOURCES
    src/accountslist.cpp
    src/accountslist.h
    src/filesave.cpp
    src/filesave.h
    src/gendoc.cpp
    src/gendoc.h
    src/initial.cpp
    src/initial.h
    src/main.cpp
    src/model.cpp
    src/model.h
    src/start.cpp
    src/start.h
    src/terminalfinances.cpp
    src/terminalfinances.h
    src/terminalfinances.ui
    src/tools.cpp
    src/tools.h
    src/updatefields.cpp
    src/updatefields.h
    src/updatefields.ui
    src/views.cpp
    src/views.h
)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
                                        Qt${QT_VERSION_MAJOR}::Widgets
                                        Qt${QT_VERSION_MAJOR}::Sql
                                        Qt${QT_VERSION_MAJOR}::PrintSupport)
