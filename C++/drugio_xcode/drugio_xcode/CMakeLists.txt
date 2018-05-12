cmake_minimum_required(VERSION 3.10)
project(drugio_xcode)

set(CMAKE_CXX_STANDARD 17)

find_package (sqlite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (drugio_xcode ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)

include_directories(namespaces/includes)
include_directories(resources)
include_directories(resources/sqlite_modern_cpp)
include_directories(resources/sqlite_modern_cpp/lists)
include_directories(resources/sqlite_modern_cpp/utility)

add_executable(drugio_xcode
        namespaces/includes/Actions.hpp
        namespaces/includes/Command.hpp
        namespaces/includes/DBConfig.hpp
        namespaces/includes/Time.hpp
        namespaces/Command.cpp
        namespaces/Drugio.cpp
        namespaces/ReturnStructures.cpp
        namespaces/Time.cpp
        resources/sqlite_modern_cpp/lists/error_codes.h
        resources/sqlite_modern_cpp/utility/function_traits.h
        resources/sqlite_modern_cpp/utility/uncaught_exceptions.h
        resources/sqlite_modern_cpp/utility/utf16_utf8.h
        resources/sqlite_modern_cpp/errors.h
        resources/sqlite_modern_cpp/log.h
        resources/sqlite_modern_cpp/sqlcipher.h
        resources/sqlite_modern_cpp/type_wrapper.h
        resources/sqlite_modern_cpp.h
        main.cpp)
