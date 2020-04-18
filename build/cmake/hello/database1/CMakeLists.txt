include(./../../ccxx/ccxx.cmake)

set(SOURCE_FILES
        main_odbc1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(hello_odbc1
        ${SOURCE_FILEPATHS})

add_dependencies(hello_odbc1
        ccxx
        ccxx_database_odbc
        )

target_link_libraries(hello_odbc1
        ccxx
        ccxx_database_odbc
        )

set_target_properties(hello_odbc1 PROPERTIES FOLDER ccxx/test)




###ccxx_sqlite

set(SOURCE_FILES
        test_sqlite1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(hello_sqlite
        ${SOURCE_FILEPATHS})

add_dependencies(hello_sqlite
        ccxx
        ccxx_database_sqlite
        )

target_link_libraries(hello_sqlite
        ccxx
        ccxx_database_sqlite
        )

set_target_properties(hello_sqlite PROPERTIES FOLDER ccxx/test)




###ccxx_cursor

set(SOURCE_FILES
        main_cursor1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(hello_cursor
        ${SOURCE_FILEPATHS})

add_dependencies(hello_cursor
        ccxx
        ccxx_database_odbc
        ccxx_database_sqlite
        )

target_link_libraries(hello_cursor
        ccxx
        ccxx_database_odbc
        ccxx_database_sqlite
        )

set_target_properties(hello_cursor PROPERTIES FOLDER ccxx/test)
