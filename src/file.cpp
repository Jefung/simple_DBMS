//
// Created by jefun on 2018/12/31.
//

#include <unistd.h>
#include "file.h"
#include <dirent.h>
#include <errno.h>
#include <fstream>

bool File::file_exists(std::string path) {
    // std::cout << path << std::endl;
    std::ifstream f(path.c_str());
    return f.good();
}

std::fstream File::append(std::string path) {
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    return fs;
}

std::ofstream File::overwrite(std::string path) {
    std::ofstream fs;
    fs.open(path);
    return fs;
}

bool File::dir_exists(std::string path) {
    DIR *dir = opendir(path.c_str());
    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return true;
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
        return false;
    } else {
        /* opendir() failed for some other reason. */
        return false;
    }
}

bool File::create_dir(std::string path) {
    if (mkdir(path.c_str(), 0777) == -1)
        return false;
    else
        return true;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
bool File::rm_dir(std::string dirname) {
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];


    // if (path == NULL) {
    //     fprintf(stderr, "Out of memory error\n");
    //     return 0;
    // }
    dir = opendir(dirname.c_str());
    if (dir == NULL) {
        perror("Error opendir()");
        return false;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            snprintf(path, (size_t) PATH_MAX, "%s/%s", dirname.c_str(), entry->d_name);
            if (entry->d_type == DT_DIR) {
                // std::string path_str(path);
                rm_dir(path);
            }
            if (rmdir(path) == -1 && remove(path) != 0)
                return false;
            // rmdir(path);

            /*
             * Here, the actual deletion must be done.  Beacuse this is
             * quite a dangerous thing to do, and this program is not very
             * well tested, we are just printing as if we are deleting.
             */
            // printf("(not really) Deleting: %s\n", path);
            /*
             * When you are finished testing this and feel you are ready to do the real
             * deleting, use this: remove*STUB*(path);
             * (see "man 3 remove")
             * Please note that I DONT TAKE RESPONSIBILITY for data you delete with this!
             */
        }

    }
    closedir(dir);
    if (rmdir(dirname.c_str()) == -1 )
        return false;

    /*
     * Now the directory is emtpy, finally delete the directory itself. (Just
     * printing here, see above)
     */
    // printf("(not really) Deleting: %s\n", dirname);

    return true;
    // if (rmdir(path.c_str()) == -1)
    //     return false;
    // return true;
}

std::string File::get_error() {
    return strerror(errno);
}

std::ofstream File::create(std::string path) {
    return overwrite(path);
}

std::ifstream File::read(std::string path) {
    std::ifstream is;
    is.open(path);
    return is;
}

std::vector<std::string> File::traversal_dir(std::string dirname) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(dirname.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            files.push_back(ent->d_name);
            // printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        /* could not open directory */
        return {};
    }
    return files;
}

std::vector<std::string> File::match_files(std::string dirname, std::string ext_name) {
    auto files = traversal_dir(dirname);
    std::vector<std::string> res;
    for(auto it : files){
        size_t pos = it.find_last_of(".");
        std::string substr = it.substr(pos+1);
        if(substr.compare(ext_name) == 0)
            res.push_back(it);
    }
    return res;
}

void File::create_empty_file(std::string path) {
    std::fstream fs;
    fs.open(path,std::ios::out);
    fs.close();

}

bool File::file_is_empty_or_eof(std::ifstream &fs) {
    if(fs.eof())
        return true;
    size_t save_pos = fs.tellg();
    fs.seekg(0,std::ios::end);

    if(fs.tellg() == 0 || save_pos == fs.tellg()){
        return true;
    }else{
        fs.seekg(save_pos);
        return false;
    }

}

bool File::rm_file(std::string path) {
    if(remove(path.c_str()) != 0)
        return false;
    else
        return true;
}

