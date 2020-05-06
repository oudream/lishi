cmake_minimum_required(VERSION 3.5)

project(hello_httpclient1 LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
find_package(Qt5 COMPONENTS LinguistTools REQUIRED)

set(TS_FILES
        httpclient1_zh_CN.ts
        )

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
        )

mc_merge_file_path(${gs_project_hello_path}/httpclient1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

if (ANDROID)
    add_library(hello_httpclient1 SHARED
            ${SOURCE_FILEPATHS}
            )
else ()
    add_executable(hello_httpclient1
            ${SOURCE_FILEPATHS}
            )
endif ()

target_link_libraries(hello_httpclient1 PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
