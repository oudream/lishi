
#1, ccxx
#1.1, ccxx_env ( string + filesystem + config(profile) )
#1.2, ccxx_interinfo ( [env] + [log](thread) )
#1.3, ccxx_simple ( [env] + [log] + system + container + math + buffer + crc + xml + socket + process + database + encoding + uuuid + procmutex + winreg)
#2, odbc
#3, sqlite
#4, lua
#5, regexp
#6, qt
#7, lua.base
#8, lua.ccxx

#1, ccxx
#gs_project_src_path

set(gs_ccxx_path ${gs_project_3rd_path}/ccxx)
set(gs_ccxx_source_path ${gs_ccxx_path}/ccxx)

include_directories(${gs_ccxx_path})
include_directories(${gs_ccxx_source_path})

set(gsl_ccxx_heads
        readme.txt
        cxglobal.h
        cxappenv.h
        cxapplication.h
        cxsystem.h
        cxcontainer.h
        cxstring.h
        cxmath.h
        cxbuffer.h
        cxpacket.h
        cxcrc.h
        cxfile.h
        cxthread.h
        cxtime.h
        cxtimer.h
        cxlog.h
        cxinterinfo.h
        cxcontext.h
        cxdescribe.h
        cxprofile.h
        cxtinyxml.h
        cxefile.h
        cxsharememory.h
        cxsocket.h
        cxbitmap.h
        cxprocess.h
        cxprofile_skv_xml.h
        cxprofile_skv_json.h
        cxchannel_global.h
        cxchannel.h
        cxchannel_tcpclient.h
        cxchannel_tcpserver.h
        cxchannel_udp.h
        cxchannel_serial.h
        cxchannel_none.h
        cxsafequeue.h
        cxsafethread.h
        cxsafebuffer.h
        cxdatabase.h
        cxbusiness.h
        cxencoding.h
        cxresource.h
        cxrapidjson.h
        cxuuid.h
        cxprocmutex.h
        cxwinreg.h
        )

set(gsl_ccxx_sources
        cxglobal.cpp
        cxappenv.cpp
        cxapplication.cpp
        cxsystem.cpp
        cxstring.cpp
        cxmath.cpp
        cxbuffer.cpp
        cxpacket.cpp
        cxcrc.cpp
        cxfile.cpp
        cxthread.cpp
        cxtime.cpp
        cxtimer.cpp
        cxlog.cpp
        cxcontext.cpp
        cxdescribe.cpp
        cxinterinfo.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        cxtinyxml.cpp
        cxefile.cpp
        cxsharememory.cpp
        cxsocket.cpp
        cxbitmap.cpp
        cxprocess.cpp
        cxprofile.cpp
        cxprofile_skv_xml.cpp
        cxprofile_skv_json.cpp
        cxchannel.cpp
        cxchannel_tcpclient.cpp
        cxchannel_tcpserver.cpp
        cxchannel_udp.cpp
        cxchannel_serial.cpp
        cxchannel_none.cpp
        cxsafebuffer.cpp
        cxdatabase.cpp
        cxbusiness.cpp
        cxencoding.cpp
        cxchannel_factorymanager.cpp
        cxprofile_factorymanager.cpp
        cxdescribe_factorymanager.cpp
        cxresource.cpp
        cxrapidjson.cpp
        cxuuid.cpp
        cxprocmutex.cpp
        cxwinreg.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_heads}" gsl_ccxx_head_filepaths)
mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_sources}" gsl_ccxx_source_filepaths)

macro(mc_ccxx_include)
    source_group("ccxx" FILES ${gsl_ccxx_head_filepaths} ${gsl_ccxx_source_filepaths})
endmacro()


#1.1, ccxx_env ( string + filesystem + config(profile) )
set(gsl_ccxx_env_heads
        cxglobal.h
        cxstring.h
        cxtime.h
        cxfile.h
        cxappenv.h
        cxprofile.h
        cxrapidjson.h
        cxprofile_skv_json.h
        )

set(gsl_ccxx_env_sources
        cxglobal.cpp
        cxstring.cpp
        cxtime.cpp
        cxfile.cpp
        cxappenv.cpp
        cxprofile.cpp
        cxrapidjson.cpp
        cxprofile_skv_json.cpp
        cxprofile_factorymanager.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_env_heads}" gsl_ccxx_env_head_filepaths)
mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_env_sources}" gsl_ccxx_env_source_filepaths)

macro(mc_ccxx_env_include)
    source_group("ccxx" FILES ${gsl_ccxx_env_head_filepaths} ${gsl_ccxx_env_source_filepaths})
    add_definitions(-D"GM_BUILD_CCXX_CORE_CODE")
    add_definitions(-D"GM_PROJECT_XML_NULL")
endmacro()


#1.2, ccxx_interinfo ( [env] + [log](thread) )
set(gsl_ccxx_interinfo_heads
        cxglobal.h
        cxstring.h
        cxtime.h
        cxfile.h
        cxappenv.h
        cxprofile.h
        cxrapidjson.h
        cxprofile_skv_json.h
        cxthread.h
        cxinterinfo.h
        cxlog.h
        )

set(gsl_ccxx_interinfo_sources
        cxglobal.cpp
        cxstring.cpp
        cxtime.cpp
        cxfile.cpp
        cxappenv.cpp
        cxprofile.cpp
        cxrapidjson.cpp
        cxprofile_skv_json.cpp
        cxprofile_factorymanager.cpp
        cxthread.cpp
        cxinterinfo.cpp
        cxlog.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_interinfo_heads}" gsl_ccxx_interinfo_head_filepaths)
mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_interinfo_sources}" gsl_ccxx_interinfo_source_filepaths)

macro(mc_ccxx_interinfo_include)
    source_group("ccxx" FILES ${gsl_ccxx_interinfo_head_filepaths} ${gsl_ccxx_interinfo_source_filepaths})
    add_definitions(-D"GM_BUILD_CCXX_CORE_CODE")
    add_definitions(-D"GM_PROJECT_XML_NULL")
endmacro()


#1.3, ccxx_simple ( [env] + [log] + system + container + math + buffer + crc + xml + socket + process + database + encoding + uuuid + procmutex + winreg)
set(gsl_ccxx_simple_heads
        cxglobal.h
        cxstring.h
        cxtime.h
        cxfile.h
        cxappenv.h
        cxprofile.h
        cxrapidjson.h
        cxprofile_skv_json.h
        cxthread.h
        cxinterinfo.h
        cxlog.h
        cxsystem.h
        cxcontainer.h
        cxmath.h
        cxbuffer.h
        cxcrc.h
        cxtinyxml.h
        cxprofile_skv_xml.h
        cxsocket.h
        cxprocess.h
        cxdatabase.h
        cxencoding.h
        cxuuid.h
        cxprocmutex.h
        cxwinreg.h
        )

set(gsl_ccxx_simple_sources
        cxglobal.cpp
        cxstring.cpp
        cxtime.cpp
        cxfile.cpp
        cxappenv.cpp
        cxprofile.cpp
        cxrapidjson.cpp
        cxprofile_skv_json.cpp
        cxprofile_factorymanager.cpp
        cxthread.cpp
        cxinterinfo.cpp
        cxlog.cpp
        cxsystem.cpp
        cxmath.cpp
        cxbuffer.cpp
        cxcrc.cpp
        cxtinyxml.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        cxprofile_skv_xml.cpp
        cxsocket.cpp
        cxprocess.cpp
        cxdatabase.cpp
        cxencoding.cpp
        cxuuid.cpp
        cxprocmutex.cpp
        cxwinreg.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_simple_heads}" gsl_ccxx_simple_head_filepaths)
mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_simple_sources}" gsl_ccxx_simple_source_filepaths)

macro(mc_ccxx_simple_include)
    source_group("ccxx" FILES ${gsl_ccxx_simple_head_filepaths} ${gsl_ccxx_simple_source_filepaths})
    add_definitions(-D"GM_BUILD_CCXX_CORE_CODE")
    add_definitions(-D"GM_PROJECT_CXAPPLICATION_NULL")
#    win32 : target_link_libraries(xxxx wsock32 ws2_32 psapi)
endmacro()


#2, odbc
set(gs_ccxx_odbc_files
        otl/otlv4.h
        cxdatabase_odbc.h
        cxdatabase_odbc.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gs_ccxx_odbc_files}" gs_ccxx_odbc_filepaths)

macro(mc_ccxx_odbc_include)
    source_group("ccxx_odbc" FILES ${gs_ccxx_odbc_filepaths})
#    WIN32 : target_link_libraries(libccxx_database_odbc odbc32 Ole32)
endmacro()


#3, sqlite
set(gs_ccxx_sqlite_files
        cxdatabase_sqlite.h
        sqlite3/sqlite3.h
        sqlite3/sqlite3ext.h
        cxdatabase_sqlite.cpp
        sqlite3/sqlite3.c
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gs_ccxx_sqlite_files}" gs_ccxx_sqlite_filepaths)

macro(mc_ccxx_sqlite_include)
    source_group("ccxx_sqlite" FILES ${gs_ccxx_sqlite_filepaths})
endmacro()


#4, lua
set(gs_ccxx_lua_path ${gs_project_3rd_path}/lua-5.3.4)
set(gs_ccxx_lua_include_path ${gs_project_include_path}/lua-5.3.4)

set(gsl_lua_headers
        src/lapi.h
        src/lauxlib.h
        src/lcode.h
        src/lctype.h
        src/ldebug.h
        src/ldo.h
        src/lfunc.h
        src/lgc.h
        src/llex.h
        src/llimits.h
        src/lmem.h
        src/lobject.h
        src/lopcodes.h
        src/lparser.h
        src/lstate.h
        src/lstring.h
        src/ltable.h
        src/ltm.h
        src/lua.h
        src/luaconf.h
        src/lualib.h
        src/lundump.h
        src/lvm.h
        src/lzio.h
        )

set(gsl_lua_sources
        src/lapi.c
        src/lauxlib.c
        src/lbaselib.c
        src/lbitlib.c
        src/lcode.c
        src/lcorolib.c
        src/lctype.c
        src/ldblib.c
        src/ldebug.c
        src/ldo.c
        src/ldump.c
        src/lfunc.c
        src/lgc.c
        src/linit.c
        src/liolib.c
        src/llex.c
        src/lmathlib.c
        src/lmem.c
        src/loadlib.c
        src/lobject.c
        src/lopcodes.c
        src/loslib.c
        src/lparser.c
        src/lstate.c
        src/lstring.c
        src/lstrlib.c
        src/ltable.c
        src/ltablib.c
        src/ltm.c
        src/lundump.c
        src/lutf8lib.c
        src/lvm.c
        src/lzio.c
        )

mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_headers}" gsl_lua_header_filepaths)
mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_sources}" gsl_lua_source_filepaths)

macro(mc_ccxx_lua_include)
    include_directories(${gs_ccxx_lua_include_path})
    source_group("ccxx_lua" FILES ${gsl_lua_header_filepaths} ${gsl_lua_source_filepaths})
endmacro()


#5, regexp
set(gs_ccxx_regexp_path ${gs_ccxx_source_path}/regexp)

set(gsl_regexp_headers
        re2/filtered_re2.h
        re2/prefilter.h
        re2/prefilter_tree.h
        re2/prog.h
        re2/re2.h
        re2/regexp.h
        re2/set.h
        re2/stringpiece.h
        re2/unicode_casefold.h
        re2/unicode_groups.h
        re2/variadic_function.h
        re2/walker-inl.h
        util/atomicops.h
        util/flags.h
        util/logging.h
        util/mutex.h
        util/sparse_array.h
        util/sparse_set.h
        util/utf.h
        util/util.h
        util/pcre.h
        )

set(gsl_regexp_sources
        re2/bitstate.cc
        re2/compile.cc
        re2/dfa.cc
        re2/filtered_re2.cc
        re2/mimics_pcre.cc
        re2/nfa.cc
        re2/onepass.cc
        re2/parse.cc
        re2/perl_groups.cc
        re2/prefilter.cc
        re2/prefilter_tree.cc
        re2/prog.cc
        re2/re2.cc
        re2/regexp.cc
        re2/set.cc
        re2/simplify.cc
        re2/stringpiece.cc
        re2/tostring.cc
        re2/unicode_casefold.cc
        re2/unicode_groups.cc
        util/rune.cc
        util/strutil.cc
        util/pcre.cc
        )

mc_merge_file_path(${gs_ccxx_regexp_path} "${gsl_regexp_headers}" gsl_regexp_header_filepaths)
mc_merge_file_path(${gs_ccxx_regexp_path} "${gsl_regexp_sources}" gsl_regexp_source_filepaths)

macro(mc_ccxx_regexp_include)
    include_directories(${gs_ccxx_regexp_path})
    source_group("ccxx_regexp" FILES ${gsl_regexp_header_filepaths} ${gsl_regexp_source_filepaths})
endmacro()


#6, qt
set(gsl_ccxx_qt_files
        cxqtutil.h
        cxqtutil.cpp
        cxapplication_qt.h
        cxapplication_qt.cpp
        )

mc_merge_file_path(${gs_ccxx_source_path} "${gsl_ccxx_qt_files}" gsl_ccxx_qt_filepaths)

macro(mc_ccxx_qt_include)
    source_group("ccxx_qt" FILES ${gsl_ccxx_qt_filepaths})
endmacro()


#7, lua_base
set(gsl_lua_base_heads
        lua_common.h
        lua_base.h
        lua_run.h
        )

set(gsl_lua_base_sources
        lua_common.cpp
        lua_base.cpp
        lua_run.cpp
        )

set(gs_ccxx_lua_path ${gs_ccxx_source_path}/cxlua)

mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_base_heads}" gsl_lua_base_head_filepaths)
mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_base_sources}" gsl_lua_base_source_filepaths)

macro(mc_lua_base_include)
    source_group("lua_base" FILES ${gsl_lua_base_head_filepaths} ${gsl_lua_base_source_filepaths})
endmacro()


#8, lua_ccxx
set(gsl_lua_ccxx_heads
        lua_cxtime.h
        lua_cxstring.h
        lua_cxfilesystem.h
        lua_cxappenv.h
        lua_cxinterinfo.h
        lua_cxlog.h
        lua_cxencoding.h
        lua_cxapplication.h
        )

set(gsl_lua_ccxx_sources
        lua_cxtime.cpp
        lua_cxstring.cpp
        lua_cxfilesystem.cpp
        lua_cxappenv.cpp
        lua_cxinterinfo.cpp
        lua_cxlog.cpp
        lua_cxencoding.cpp
        lua_cxapplication.cpp
        )

mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_ccxx_heads}" gsl_lua_ccxx_head_filepaths)
mc_merge_file_path(${gs_ccxx_lua_path} "${gsl_lua_ccxx_sources}" gsl_lua_ccxx_source_filepaths)

macro(mc_lua_ccxx_include)
    source_group("lua_ccxx" FILES ${gsl_lua_ccxx_head_filepaths} ${gsl_lua_ccxx_source_filepaths})
endmacro()
