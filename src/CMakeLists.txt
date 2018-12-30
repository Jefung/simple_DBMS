# 设置入口文件,将除入口文件外的其他文件打包为库文件,供入口文件和单元测试使用
set(MAIN_FILE main.cpp)

# 将当前目录下所有.cpp/.h文件包含进来. 注意,file()必须在每次增加/删除文件时reload project
file(GLOB_RECURSE source_files "*.cpp" "*.h")
# 去除入口文件
list(REMOVE_ITEM source_files MAIN_FILE)

# 打包成库
add_library(${CMAKE_PROJECT_NAME}_lib ${source_files})

# 生成可执行文件
add_executable(${CMAKE_PROJECT_NAME}_run ${MAIN_FILE})
target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)
