cmake_minimum_required (VERSION 3.10)


################
## Project
#########################
project(modest LANGUAGES C)


################
## User choices
#########################
option(MODEST_BUILD_SHARED "Build shared library" ON)
option(MODEST_BUILD_STATIC "Build static library" ON)
option(MyHTML_BUILD_WITHOUT_THREADS "Build MyHTML without POSIX Threads" OFF)
option(MyCORE_BUILD_WITHOUT_THREADS "Build MyCORE without POSIX Threads" OFF)
option(MODEST_INSTALL_HEADERS "Install header files" ON)
set(CMAKE_C_STANDARD 99 CACHE STRING "desired compilation C standard: 90, 99, 11")
#set_property(CACHE CMAKE_C_STANDARD PROPERTY STRINGS 90 99 11)
option(CMAKE_C_STANDARD_REQUIRED "don't compile using a previous C standard if the one specified is not met" ON)
#set(CMAKE_CXX_STANDARD 11 CACHE STRING "desired compilation C++ standard: 98, 11, 14, 17, 20")
#set_property(CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS 98 11 14 17 20)
#option(CMAKE_CXX_STANDARD_REQUIRED "don't compile using a previous C++ standard if the one specified is not met" ON)
#option(CMAKE_CXX_EXTENSIONS "compile using C++ standard extensions" FALSE)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Suffix for debug binaries")


################
## Dependencies
#########################
if(NOT MyHTML_BUILD_WITHOUT_THREADS OR NOT MyCORE_BUILD_WITHOUT_THREADS)
    set(CMAKE_THREAD_PREFER_PTHREAD 1)
    find_package(Threads REQUIRED)
    if(NOT CMAKE_USE_PTHREADS_INIT)
        message(FATAL_ERROR "Could NOT find pthreads (missing: CMAKE_USE_PTHREADS_INIT)")
    endif()
endif()


################
## Project Version
#########################
set(PROJECT_VERSION_HEADER_FILE "${CMAKE_CURRENT_LIST_DIR}/include/modest/myosi.h")

file(STRINGS ${PROJECT_VERSION_HEADER_FILE} PROJECT_VERSION_PARTS
REGEX "^#define[ \t]+MODEST_VERSION_(MAJOR|MINOR|PATCH)[ \t]+[0-9]+$")

list(GET PROJECT_VERSION_PARTS 0 PROJECT_VERSION_MAJOR_PART)
list(GET PROJECT_VERSION_PARTS 1 PROJECT_VERSION_MINOR_PART)
list(GET PROJECT_VERSION_PARTS 2 PROJECT_VERSION_PATCH_PART)

string(REGEX REPLACE "#define[ \t]+MODEST_VERSION_MAJOR[ \t]+([0-9]+).*" "\\1" PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR_PART})
string(REGEX REPLACE "#define[ \t]+MODEST_VERSION_MINOR[ \t]+([0-9]+).*" "\\1" PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR_PART})
string(REGEX REPLACE "#define[ \t]+MODEST_VERSION_PATCH[ \t]+([0-9]+).*" "\\1" PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH_PART})

set(PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message(STATUS "Project version: ${PROJECT_VERSION_STRING}")


################
## Turn on the ability to create folders to organize projects (.vcproj)
#########################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


################
## Includes
#########################
set(PROJECT_DIR_API_HEADER "${CMAKE_CURRENT_LIST_DIR}/include")
#file(GLOB_RECURSE PROJECT_PUBLIC_HEADERS ${PROJECT_DIR_API_HEADER}/*.h)


################
## Sources
#########################
MACRO(GET_MODULES_LIST result curdir)
FILE(GLOB children ${curdir}/ ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        string(REGEX MATCH "\\.[^/]+$" MATCHSTR ${child})
        IF(IS_DIRECTORY ${child} AND MATCHSTR STREQUAL "")
            string(REGEX MATCH "[^/]+$" MATCHSTR ${child})
            IF(NOT MATCHSTR STREQUAL "myport")
                LIST(APPEND dirlist ${MATCHSTR})
            ENDIF()
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

MACRO(CREATE_MODULES_SOURCE_PATH result dirpath modules)
    SET(dirlist "")
    FOREACH(module ${modules})
        LIST(APPEND dirlist ${dirpath}/${module}/*.c)
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

set(PROJECT_SOURCE "${CMAKE_CURRENT_LIST_DIR}/source")

GET_MODULES_LIST(MODULES ${PROJECT_SOURCE})
CREATE_MODULES_SOURCE_PATH(MODULES_PATH ${PROJECT_SOURCE} "${MODULES}")

file(GLOB_RECURSE PROJECT_SOURCES ${MODULES_PATH})

message(STATUS "Project modules: ${MODULES}")
#message(STATUS "${PROJECT_SOURCES}")


################
## Include port based on OS
#########################
set(PROJECT_SOURCE_PORT_DIR "${PROJECT_SOURCE}/myport")

if(WIN32)
    file(GLOB_RECURSE PROJECT_SOURCES_PORT ${PROJECT_SOURCE_PORT_DIR}/windows_nt/mycore/*.c ${PROJECT_SOURCE_PORT_DIR}/windows_nt/mycore/*/*.c)
else()
    file(GLOB_RECURSE PROJECT_SOURCES_PORT ${PROJECT_SOURCE_PORT_DIR}/posix/mycore/*.c ${PROJECT_SOURCE_PORT_DIR}/posix/mycore/utils/*/*.c)
endif(WIN32)

message(STATUS "Port sources:")
foreach(__item IN LISTS PROJECT_SOURCES_PORT)
   message(STATUS "${__item}")
endforeach()


################
## Target properties
#########################
set(PROJECT_PRIVATE_COMPILE_DEFINITIONS "")
set(PROJECT_INTERFACE_COMPILE_DEFINITIONS "")
set(PROJECT_INTERFACE_COMPILE_OPTIONS "")
set(PROJECT_PRIVATE_COMPILE_OPTIONS "")

if (WIN32)
  if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS _WIN64)
  else()
    list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS _WIN32)
  endif()
endif()


if(MSVC)
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS /wd4100 /wd4255 /wd4820 /wd4668)
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS "MODEST_BUILD_OS=Windows_NT")
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS "MODEST_PORT_NAME=windows_nt")
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS "MyCORE_OS_WINDOWS_NT")

  list(APPEND PROJECT_INTERFACE_COMPILE_DEFINITIONS "MyCORE_OS_WINDOWS_NT")
else()
  list(APPEND PROJECT_PRIVATE_COMPILE_OPTIONS -Wall -Werror -pipe -pedantic -Wno-unused-variable -Wno-unused-function)
endif()

list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS $<$<CONFIG:Debug>:MyCORE_BUILD_DEBUG> $<$<CONFIG:RelWithDebInfo>:MyCORE_BUILD_DEBUG>)

if(MyCORE_BUILD_WITHOUT_THREADS)
  message(STATUS "Build without POSIX Threads")
  list(APPEND PROJECT_PRIVATE_COMPILE_DEFINITIONS "MyCORE_BUILD_WITHOUT_THREADS")
  list(APPEND PROJECT_INTERFACE_COMPILE_DEFINITIONS "MyCORE_BUILD_WITHOUT_THREADS")
else()
  message(STATUS "Build with POSIX Threads")
endif()

#message(STATUS "Project private compile definitions: ${PROJECT_PRIVATE_COMPILE_DEFINITIONS}")


################
## Define targets: static/dynamic library
#########################
set(PROJECT_LIB_SHARED "${PROJECT_NAME}_shared")
set(PROJECT_LIB_STATIC "${PROJECT_NAME}_static")
set(PROJECT_LIB_SHARED_FILE_NAME "${PROJECT_NAME}")
if(MSVC)
   set(PROJECT_LIB_STATIC_FILE_NAME "${PROJECT_NAME}_a")
else()
   set(PROJECT_LIB_STATIC_FILE_NAME "${PROJECT_NAME}")
endif()
set(PROJECT_LIBRARY_TARGETS "")


if(MODEST_BUILD_SHARED)
   add_library(${PROJECT_LIB_SHARED} SHARED ${PROJECT_SOURCES} ${PROJECT_SOURCES_PORT})
   set_target_properties(${PROJECT_LIB_SHARED} PROPERTIES OUTPUT_NAME ${PROJECT_LIB_SHARED_FILE_NAME})
if (MSVC)
   set_target_properties(${PROJECT_LIB_SHARED} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
   list(APPEND PROJECT_LIBRARY_TARGETS ${PROJECT_LIB_SHARED})
endif()

if(MODEST_BUILD_STATIC)
   add_library(${PROJECT_LIB_STATIC} STATIC ${PROJECT_SOURCES} ${PROJECT_SOURCES_PORT})
   set_target_properties(${PROJECT_LIB_STATIC} PROPERTIES OUTPUT_NAME ${PROJECT_LIB_STATIC_FILE_NAME})
   list(APPEND PROJECT_LIBRARY_TARGETS ${PROJECT_LIB_STATIC})
endif()

foreach(__item IN LISTS PROJECT_LIBRARY_TARGETS)
    set_target_properties(${__item} PROPERTIES VERSION ${PROJECT_VERSION_STRING} SOVERSION ${PROJECT_VERSION_MAJOR})
#    target_compile_features(${__item} PRIVATE c_std_99)
#    target_compile_features(${__item} PRIVATE cxx_std_11)
    target_compile_definitions(${__item}
      INTERFACE ${PROJECT_INTERFACE_COMPILE_DEFINITIONS}
      PRIVATE ${PROJECT_PRIVATE_COMPILE_DEFINITIONS}
    )
    target_compile_options(${__item}
#      INTERFACE ${PROJECT_PRIVATE_COMPILE_OPTIONS}
      PRIVATE ${PROJECT_PRIVATE_COMPILE_OPTIONS}
    )
    target_include_directories(${__item}
      PUBLIC
         $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # <prefix>/${CMAKE_INSTALL_INCLUDEDIR}
    )
    target_link_libraries(${__item}
      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    )
endforeach()


################
## Install
#########################
if(NOT MSVC)
   include(GNUInstallDirs)
endif()

if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
   set(CMAKE_INSTALL_INCLUDEDIR "include")
endif()

if(NOT DEFINED CMAKE_INSTALL_BINDIR)
   set(CMAKE_INSTALL_BINDIR "bin")
endif()

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
   set(CMAKE_INSTALL_LIBDIR "lib")
endif()

set(MODEST_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake" CACHE PATH
   "install location of folder with project cmake config files, either relative to CMAKE_INSTALL_PREFIX, or an absolute path")


if(MODEST_INSTALL_HEADERS)
   install(DIRECTORY "${PROJECT_DIR_API_HEADER}/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" FILES_MATCHING PATTERN "*.h")
endif()

install(TARGETS ${PROJECT_LIBRARY_TARGETS} EXPORT ${PROJECT_NAME}
   RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
   LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   #PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
   #INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
   )

#Use this to change the exported target name to be different than the defined target name
#set_target_properties(modest_shared PROPERTIES EXPORT_NAME Modest_shared)

if(MSVC)
   install(FILES "$<TARGET_PDB_FILE:${PROJECT_LIB_SHARED}>" DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL)
endif()


#this makes an IMPORTED targets definition file which is specific to the build tree, and is not relocatable
#export(EXPORT ${PROJECT_NAME} FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.cmake NAMESPACE JSONUtils::)


#this makes an IMPORTED targets definition file which is relocatable
install(
   EXPORT ${PROJECT_NAME}
   NAMESPACE ${PROJECT_NAME}::
   DESTINATION "${MODEST_INSTALL_CONFIGDIR}"
   FILE ${PROJECT_NAME}.cmake
   CONFIGURATIONS Debug Release
   )

include(CMakePackageConfigHelpers)

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Config.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
   INSTALL_DESTINATION ${MODEST_INSTALL_CONFIGDIR}
   PATH_VARS
      MODEST_INSTALL_CONFIGDIR
   )

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
   VERSION ${PROJECT_VERSION_STRING}
   COMPATIBILITY AnyNewerVersion
   )

#Install the config, configversion and custom find modules
install(FILES
#   ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
   DESTINATION ${MODEST_INSTALL_CONFIGDIR}
   )

#Register package in user's package registry
#export(PACKAGE ${PROJECT_NAME})


#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(${PROJECT_NAME}::${PROJECT_LIB_SHARED} ALIAS ${PROJECT_LIB_SHARED})
add_library(${PROJECT_NAME}::${PROJECT_LIB_STATIC} ALIAS ${PROJECT_LIB_STATIC})


################
## Build a package
#########################
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fast C/C++ HTML 5 Renderer. Using threads.")
set(CPACK_PACKAGE_CONTACT "lex.borisov@gmail.com (Alexander Borisov)")
set(CPACK_PACKAGE_VENDOR "Alexander Borisov")

set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION_STRING})

if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
  set(CPACK_RPM_PACKAGE_ARCHITECTURE i686)
else()
  set(CPACK_RPM_PACKAGE_ARCHITECTURE x86_64)
endif()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_ARCHITECTURE}")

include(CPack)
