cmake_minimum_required(VERSION 3.5)

project(lishi-db-tool LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(Qt5 COMPONENTS LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS WebEngineCore WebEngine WebEngineWidgets WebView WebChannel WebSockets REQUIRED)

set(TS_FILES lishi-db-tool_zh_CN.ts)
set(QRC_FILES data/simplebrowser.qrc)

set(SOURCE_FILES
        # h
        mainwindow.h
        # cpp
        main.cpp
        mainwindow.cpp
        # ui
        mainwindow.ui
        #
        ${TS_FILES}
        #
        ${QRC_FILES}
        )

mc_merge_file_path(${gs_project_projects_path}/lishi-db-tool "${SOURCE_FILES}" SOURCE_FILEPATHS)

include(./../../ccxx/ccxx.cmake)
mc_ccxx_qt_include()
mc_ccxx_sqlite_include()

if (ANDROID)
    add_library(lishi-db-tool SHARED
            ${SOURCE_FILEPATHS}
            ${gsl_ccxx_qt_filepaths}
            )
else ()
    add_executable(lishi-db-tool
            ${SOURCE_FILEPATHS}
            ${gsl_ccxx_qt_filepaths}
            )
endif ()

target_link_libraries(lishi-db-tool PRIVATE
        Qt5::WebEngineCore
        Qt5::WebEngine
        Qt5::WebEngineWidgets
        Qt5::WebView
        Qt5::WebChannel
        Qt5::Widgets
        ccxx
        ccxx_database_sqlite
        )

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
