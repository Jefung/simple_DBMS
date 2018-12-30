# DBMS
## Todo
- [x] 以实现的功能
- [ ] 待实现的功能

## 目录结构
```bash
├─docs : 项目文档相关资料
│      Doxyfile
├─cmake-build-debug
│  │
│  ├─lib : 默认生成库所在目录
│  │
│  └─bin : 默认可执行文件(项目的可执行文件,单元测试的可执行文件)所在目录
│
├─src : 源代码
│      CMakeLists.txt
│      main.cpp : 入口文件
│
├─tests : 单元测试
│      CMakeLists.txt
│      common.cpp
│      common.h : 测试文件共用函数/类
│      test_example.cpp : googletest的demo,方便写测试文件时可用
│
└─third_lib : 第三方库所在目录(如googletest)
```

## 如何使用?

