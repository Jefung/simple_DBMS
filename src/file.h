//
// Created by jefun on 2018/12/31.
//
// comment: 文件操作类
#ifndef DBMS_FILE_H
#define DBMS_FILE_H


#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string>

// struct _finddata_t
// {
// unsigned attrib;
// time_t time_create;
// time_t time_access;
// time_t time_write;
// _fsize_t size;
// char name[_MAX_FNAME];
// };

class File {
public:
    static bool file_exists(std::string path);

    static void create_empty_file(std::string path);

    static bool file_is_empty_or_eof(std::ifstream &fs);

    static std::string get_error();

    static std::fstream append(std::string path);

    static std::ofstream overwrite(std::string path);

    static std::ifstream read(std::string path);

    static bool dir_exists(std::string path);

    static bool create_dir(std::string path);

    static std::ofstream create(std::string path);

    static bool rm_dir(std::string path);

    static bool rm_file(std::string path);

    static std::vector<std::string> traversal_dir(std::string dirname);

    static std::vector<std::string> match_files(std::string dirname, std::string ext_name);
};


#endif //DBMS_FILE_H
