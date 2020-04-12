cmake_minimum_required(VERSION 3.5)

project(hello_widgetweb2 LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Widgets Core Gui Xml Network REQUIRED)
find_package(Qt5 COMPONENTS WebEngineCore WebEngine WebEngineWidgets WebView WebChannel WebSockets REQUIRED)

set(TS_FILES widgetweb2_zh_CN.ts)
set(QRC_FILES data/simplebrowser.qrc)

set(SOURCE_FILES
        # h
        browser.h
        browserwindow.h
        downloadmanagerwidget.h
        downloadwidget.h
        tabwidget.h
        webpage.h
        webpopupwindow.h
        webview.h
        mainwindow.h
        # cpp
        browser.cpp
        browserwindow.cpp
        downloadmanagerwidget.cpp
        downloadwidget.cpp
        main.cpp
        tabwidget.cpp
        webpage.cpp
        webpopupwindow.cpp
        webview.cpp
        mainwindow.cpp
        # ui
        certificateerrordialog.ui
        passworddialog.ui
        downloadmanagerwidget.ui
        downloadwidget.ui
        mainwindow.ui
        #
        ${TS_FILES}
        #
        ${QRC_FILES}
        )

mc_merge_file_path(${gs_project_hello_path}/widgetweb2 "${SOURCE_FILES}" SOURCE_FILEPATHS)

if(ANDROID)
  add_library(hello_widgetweb2 SHARED
    ${SOURCE_FILEPATHS}
  )
else()
  add_executable(hello_widgetweb2
    ${SOURCE_FILEPATHS}
  )
endif()

target_link_libraries(hello_widgetweb2 PRIVATE
        Qt5::WebEngineCore
        Qt5::WebEngine
        Qt5::WebEngineWidgets
        Qt5::WebView
        Qt5::WebChannel
        Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
