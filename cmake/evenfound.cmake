SET(CMAKE_CXX_STANDARD              17)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Werror")
SET(CMAKE_CXX_FLAGS_DEBUG   "-g3 -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3")


MACRO(EF_ADD_TEST testname)
    ADD_EXECUTABLE(test_${testname}
        ${testname}.cpp
    )
    TARGET_INCLUDE_DIRECTORIES(test_${testname}
        PRIVATE ${EF_GEN_INCLUDE_DIR}
    )
    TARGET_LINK_LIBRARIES(test_${testname}
        ${EVENFOUND_LIBRARY}
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
    )
    ADD_TEST(
        NAME    ${testname}
        COMMAND $<TARGET_FILE:test_${testname}>
    )
ENDMACRO(EF_ADD_TEST)
