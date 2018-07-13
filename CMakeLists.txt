CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
PROJECT(evenfound CXX)

INCLUDE(cmake/evenfound.cmake)

#
#   CONFIGURE PATHS
#
SET(EVENFOUND_LIBRARY   evenfound   CACHE STRING "library name")
SET(NODE_EXECUTABLE     node        CACHE STRING "node executable name")

SET(EF_KEYS_DIR         ${CMAKE_BINARY_DIR}/keys/private    CACHE STRING "directory to store generated private keys")
SET(EF_PUBKEYS_DIR      ${CMAKE_BINARY_DIR}/keys/public     CACHE STRING "directory to store generated public keys")
SET(EF_RSA_KEY_LENGTH   1024                                CACHE STRING "RSA key length")
SET(EF_GEN_INCLUDE_DIR  ${CMAKE_BINARY_DIR}/include         CACHE STRING "generated headers include directory")


FIND_PACKAGE(Boost COMPONENTS system program_options REQUIRED)


#
#   FIND ALL DEPENDENCIES
#
FIND_LIBRARY(GMP_LIBRARY        NAMES gmp)
FIND_LIBRARY(GTEST_LIBRARY      NAMES gtest)
FIND_LIBRARY(GTEST_MAIN_LIBRARY NAMES gtest_main)

MESSAGE(STATUS "GMP_LIBRARY        => ${GMP_LIBRARY}")
MESSAGE(STATUS "GTEST_LIBRARY      => ${GTEST_LIBRARY}")
MESSAGE(STATUS "GTEST_MAIN_LIBRARY => ${GTEST_MAIN_LIBRARY}")


IF(NOT GMP_LIBRARY)
    MESSAGE(FATAL "GMP library is required")
ENDIF(NOT GMP_LIBRARY)

IF(NOT Boost_LIBRARIES)
    MESSAGE(FATAL "Boost libraries are required")
ENDIF(NOT Boost_LIBRARIES)

#
#   ADD SUBDIRECTORIES
#
ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(library_evenfound)
ADD_SUBDIRECTORY(node)


#
#   ENABLE TESTS
#
IF (GTEST_LIBRARY AND GTEST_MAIN_LIBRARY)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
