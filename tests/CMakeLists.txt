# 将gtest所需要的头文件目录加入查找路径中
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 将项目根目录下的/src加入文件查找路径中,方便test测试文件包括项目头文件
# ps: ${CMAKE_SOURCE_DIR} 是项目根目录,
#    ${PROJECT_SOURCE_DIR} 是最近一个使用了project()函数的CMakeLists.txt所在目录
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

# 将test_开头的文件视为单元测试文件, common.cpp是测试文件的共用文件(函数,类...)
file(GLOB_RECURSE test_files "test_*.cpp")
add_executable(Unit_Tests_run ${test_files} common.cpp)

# 链接gtest的库
target_link_libraries(Unit_Tests_run gtest gtest_main)
# 链接自己项目的库(库在src/CMakeLists.txt中生成)
target_link_libraries(Unit_Tests_run ${CMAKE_PROJECT_NAME}_lib)
