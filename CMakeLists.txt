cmake_minimum_required(VERSION 3.5)

project(BlockSecurity VERSION 0.1 LANGUAGES CXX)
#set(RESOURCE_FILES "data/icon/key.png")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS src/panelenterpasswd/)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/worktxt/)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/mainwindow/)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/autorun/)

set(CMAKE_AUTOUIC_SEARCH_PATHS src/bluetooth/)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/database/)

set(CMAKE_AUTOUIC_SEARCH_PATHS src/error/)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Bluetooth)

set(PROJECT_SOURCES
    src/main.cpp

    src/mainwindow/mainwindow.cpp
    src/mainwindow/mainwindow.h
    src/mainwindow/mainwindow.ui

    src/panelenterpasswd/panelenterpasswd.cpp
    src/panelenterpasswd/panelenterpasswd.h
    src/panelenterpasswd/panelenterpasswd.ui

    src/worktxt/workfiletxt.cpp
    src/worktxt/workfiletxt.h

    src/autorun/autorun.h
    src/autorun/autorun.cpp


    src/database/workdatabase.cpp
    src/database/workdatabase.h

    src/bluetooth/bluetooth.h
    src/bluetooth/bluetooth.cpp

    src/error/error.h
    src/error/error.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/src/panelenterpasswd/")
include_directories("${CMAKE_SOURCE_DIR}/src/worktxt/")
include_directories("${CMAKE_SOURCE_DIR}/src/mainwindow/")
include_directories("${CMAKE_SOURCE_DIR}/src/autorun/")

include_directories("${CMAKE_SOURCE_DIR}/src/database/")
include_directories("${CMAKE_SOURCE_DIR}/src/bluetooth/")

include_directories("${CMAKE_SOURCE_DIR}/src/error/")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BlockSecurity
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/panelenterpasswd/panelenterpasswd.h
        src/panelenterpasswd/panelenterpasswd.cpp
        src/panelenterpasswd/panelenterpasswd.ui

        src/mainwindow/mainwindow.h
        src/mainwindow/mainwindow.cpp
        src/mainwindow/mainwindow.ui

        src/worktxt/workfiletxt.cpp
        src/worktxt/workfiletxt.h

        src/autorun/autorun.h
        src/autorun/autorun.cpp

        src/error/error.h
        src/error/error.cpp

        src/database/workdatabase.cpp
        src/database/workdatabase.h

        src/bluetooth/bluetooth.h
        src/bluetooth/bluetooth.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Diplom APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BlockSecurity SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BlockSecurity
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BlockSecurity PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(BlockSecurity PRIVATE Qt6::Core Qt6::Sql)
target_link_libraries(BlockSecurity PRIVATE Qt6::Bluetooth)
target_link_libraries(BlockSecurity PRIVATE BluetoothAPIs)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BlockSecurity)
endif()
set_target_properties(BlockSecurity PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BlockSecurity
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BlockSecurity)
endif()
