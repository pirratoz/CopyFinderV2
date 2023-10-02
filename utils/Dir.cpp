//
// Created by pirratoz on 30.09.23.
//

#include <algorithm>
#include <experimental/filesystem>

#include "Dir.h"


namespace fs = std::experimental::filesystem;
using std::all_of;


bool Dir::is_dir(string &path) {
    return fs::is_directory(path);
}

bool Dir::is_exists(string &path) {
    return fs::exists(path);
}

bool Dir::find_epath(string &path, list<string> epaths) {
    return all_of(epaths.begin(), epaths.end(), [path](const std::string& mask){
       return path.find(mask) == std::string::npos;
   });
}
