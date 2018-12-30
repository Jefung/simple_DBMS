cmake_minimum_required(VERSION 3.9)
project(DBMS)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(tests)

# 编译时如果找不到google库,自动去github下载到 项目根目录/third_lib/googletest
set(GOOGLETEST_DIR ${CMAKE_SOURCE_DIR}/third_lib/googletest)
if (NOT EXISTS ${GOOGLETEST_DIR})
    find_package(Git REQUIRED)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest ${GOOGLETEST_DIR}
    )
endif ()
add_subdirectory(third_lib/googletest)

# Doxygen 构建(本人尚未使用,先空置)
option(BUILD_DOC "Build Documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if (NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif ()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen buld started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif (DOXYGEN_FOUND)


# 附上个人经常使用的配置
## 加上boost编译
# find_package(Boost 1.58.0 COMPONENTS system filesystem REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# target_link_libraries(可执行文件名 ${Boost_LIBRARIES})