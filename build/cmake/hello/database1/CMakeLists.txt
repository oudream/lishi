set(SOURCE_FILES
        main_odbc1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(lishi_hello_database1
        ${SOURCE_FILEPATHS})

add_dependencies(lishi_hello_database1
        ccxx
        ccxx_database_odbc
        )

target_link_libraries(lishi_hello_database1
        ccxx
        ccxx_database_odbc
        )

set_target_properties(lishi_hello_database1 PROPERTIES FOLDER ccxx/test)




###ccxx_sqlite

set(SOURCE_FILES
        main_sqlite1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(cxtest_database_sqlite
        ${SOURCE_FILEPATHS})

add_dependencies(cxtest_database_sqlite
        ccxx
        ccxx_database_sqlite
        )

target_link_libraries(cxtest_database_sqlite
        ccxx
        ccxx_database_sqlite
        )

set_target_properties(cxtest_database_sqlite PROPERTIES FOLDER ccxx/test)




###ccxx_cursor

set(SOURCE_FILES
        main_cursor1.cpp
        )

mc_merge_file_path(${gs_project_hello_path}/database1 "${SOURCE_FILES}" SOURCE_FILEPATHS)

add_executable(cxtest_database_cursor
        ${SOURCE_FILEPATHS})

add_dependencies(cxtest_database_cursor
        ccxx
        ccxx_database_odbc
        ccxx_database_sqlite
        )

target_link_libraries(cxtest_database_cursor
        ccxx
        ccxx_database_odbc
        ccxx_database_sqlite
        )

set_target_properties(cxtest_database_cursor PROPERTIES FOLDER ccxx/test)
