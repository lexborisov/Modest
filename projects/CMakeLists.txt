cmake_minimum_required( VERSION 2.8.8 )

################
## version and path
#########################
set(MODEST_PROJECT_NAME "modest")
set(MODEST_PROJECT_DIR_ROOT "..")
set(MODEST_PROJECT_DIR_LIB "${MODEST_PROJECT_DIR_ROOT}/lib")
set(MODEST_PROJECT_API_HEADER "${MODEST_PROJECT_DIR_ROOT}/include/")
set(MODEST_PROJECT_SOURCE "${MODEST_PROJECT_DIR_ROOT}/source")

set(MODEST_VERSION_MAJOR 0)
set(MODEST_VERSION_MINOR 0)
set(MODEST_VERSION_PATCH 1)
set(MODEST_VERSION_STRING "${MODEST_VERSION_MAJOR}.${MODEST_VERSION_MINOR}.${MODEST_VERSION_PATCH}")

project(${MODEST_PROJECT_NAME})

################
## Detect OS
#########################
set(MODEST_PLATFORM "UNDEF")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(EXISTS "/etc/debian_version")
    set(MODEST_PLATFORM "Debian")
  endif(EXISTS "/etc/debian_version")
  
  if(EXISTS "/etc/redhat-release")
    set(MODEST_PLATFORM "Redhat")
  endif(EXISTS "/etc/redhat-release")
  
  if(EXISTS "/etc/fedora-release")
    set(MODEST_PLATFORM "Redhat")
  endif(EXISTS "/etc/fedora-release")
  
  if(EXISTS "/etc/SuSE-release")
    set(MODEST_PLATFORM "SuSe")
  endif(EXISTS "/etc/SuSE-release")
  
  if(EXISTS "/etc/gentoo-release")
    set(MODEST_PLATFORM "Gentoo")
  endif(EXISTS "/etc/gentoo-release")
endif()

################
## lib param
#########################
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 OLD)
endif()

set(MODEST_PROJECT_LIB_NAME "${MODEST_PROJECT_NAME}")
set(MODEST_PROJECT_LIB_NAME_STATIC "${MODEST_PROJECT_NAME}_static")

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR "lib")
endif()

if(NOT DEFINED MODEST_OPTIMIZATION_LEVEL)
  set(MODEST_OPTIMIZATION_LEVEL "-O2")
endif()

if(NOT DEFINED MODEST_BUILD_WITHOUT_THREADS)
    set(MODEST_BUILD_WITHOUT_THREADS "NO")
endif()

################
## extern mem functions
#########################
if(DEFINED MODEST_EXTERN_MALLOC)
    add_definitions(-DMODEST_EXTERN_MALLOC=${MODEST_EXTERN_MALLOC})
endif()

if(DEFINED MODEST_EXTERN_REALLOC)
    add_definitions(-DMODEST_EXTERN_REALLOC=${MODEST_EXTERN_REALLOC})
endif()

if(DEFINED MODEST_EXTERN_CALLOC)
    add_definitions(-DMODEST_EXTERN_CALLOC=${MODEST_EXTERN_CALLOC})
endif()

if(DEFINED MODEST_EXTERN_FREE)
    add_definitions(-DMODEST_EXTERN_FREE=${MODEST_EXTERN_FREE})
endif()

################
## ARGS
#########################
set(INSTALL_DLL_EXE_DIR "bin")

option(MODEST_BUILD_SHARED "Build shared library" ON)
option(MODEST_BUILD_STATIC "Build static library" ON)
option(MODEST_INSTALL_HEADER "Install header files" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MODEST_OPTIMIZATION_LEVEL}")

include_directories(${MODEST_PROJECT_SOURCE})
FILE(GLOB_RECURSE ALL_SOURCE_LIST "${MODEST_PROJECT_SOURCE}/*.c")

if (!UNIX AND WIN32)
  if(${CMAKE_CL_64})
    add_definitions(-D_WIN64)
  else()
    add_definitions(-D_WIN32)
  endif()
endif()

if(${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
  add_definitions(/wd4100 /wd4255 /wd4820 /wd4668)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  
  message(STATUS "Windows set definitions")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall --std=c99 -fPIC")
  
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-D_POSIX_C_SOURCE=199309L)
  endif()
  
  if(MODEST_BUILD_WITHOUT_THREADS STREQUAL "NO")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
  endif()
endif()

if(MODEST_BUILD_WITHOUT_THREADS STREQUAL "YES")
  message(STATUS "Build without POSIX Threads")
  add_definitions(-DMODEST_BUILD_WITHOUT_THREADS)
else()
  message(STATUS "Build with POSIX Threads")
endif()

################
## build
#########################
if(MODEST_BUILD_SHARED)
  add_library(${MODEST_PROJECT_NAME} SHARED ${ALL_SOURCE_LIST})
  set_target_properties(${MODEST_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${MODEST_PROJECT_NAME})
  set_target_properties(${MODEST_PROJECT_NAME} PROPERTIES VERSION ${MODEST_VERSION_STRING} SOVERSION ${MODEST_VERSION_MAJOR})
endif()

if(MODEST_BUILD_STATIC)
  add_library(${MODEST_PROJECT_LIB_NAME_STATIC} STATIC ${ALL_SOURCE_LIST})
  set_target_properties(${MODEST_PROJECT_LIB_NAME_STATIC} PROPERTIES OUTPUT_NAME ${MODEST_PROJECT_LIB_NAME_STATIC})
  set_target_properties(${MODEST_PROJECT_LIB_NAME_STATIC} PROPERTIES VERSION ${MODEST_VERSION_STRING} SOVERSION ${MODEST_VERSION_MAJOR})
endif()

################
## install
#########################
if(MODEST_INSTALL_HEADER)
  install(DIRECTORY "${MODEST_PROJECT_API_HEADER}" DESTINATION "include" FILES_MATCHING PATTERN "*.h")
endif()

if(MODEST_BUILD_SHARED)
  install(TARGETS ${MODEST_PROJECT_LIB_NAME}
  RUNTIME DESTINATION "${INSTALL_DLL_EXE_DIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()

if(MODEST_BUILD_STATIC)
  install(TARGETS ${MODEST_PROJECT_LIB_NAME_STATIC}
  RUNTIME DESTINATION "${INSTALL_DLL_EXE_DIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()

################
## Build an RPM.
#########################
set(CPACK_PACKAGE_VERSION ${MODEST_VERSION_STRING})

if(MODEST_PLATFORM STREQUAL "Debian")
  set(CPACK_GENERATOR "DEB")
elseif(MODEST_PLATFORM STREQUAL "Redhat")
  set(CPACK_GENERATOR "RPM")
elseif(MODEST_PLATFORM STREQUAL "SuSe")
  set(CPACK_GENERATOR "RPM")
else()
  set(CPACK_GENERATOR "TGZ")
endif()

set(CPACK_PACKAGE_NAME "modest")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Modest is a fast HTML Render implemented as a pure C99 library with no outside dependencies.")
set(CPACK_PACKAGE_CONTACT "Alexander Borisov")
set(CPACK_PACKAGE_VENDOR "Alexander Borisov")

if(32BIT)
  set(CPACK_RPM_PACKAGE_ARCHITECTURE i686)
else()
  set(CPACK_RPM_PACKAGE_ARCHITECTURE x86_64)
endif()

if(MODEST_BUILD_WITHOUT_THREADS STREQUAL "YES")
  set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}-without-threads.${CPACK_RPM_PACKAGE_ARCHITECTURE}")
else()
  set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_ARCHITECTURE}")
endif()

include(CPack)
