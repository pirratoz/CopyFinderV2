//
// Created by pirratoz on 30.09.23.
//

#include <algorithm>
#include <fstream>
#include <regex>

#include "File.h"

using std::any_of;
using std::regex_match;
using std::regex;


string File::get_name(const string &path) {
    return path.substr(path.find_last_of('/') + 1);
}

unsigned File::get_size(const string &path) {
    unsigned file_size = 0;
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        file_size = file.tellg();
        file.close();
        return file_size;
    }
    return file_size;
}

bool File::find_mask(const string &path, const list<string>& masks) {
    if (masks.empty()) return true;
    std::string file_name = get_name(path);
    return any_of(masks.begin(), masks.end(), [file_name](const std::string& mask){
       return std::regex_match(file_name, regex(mask));
   });
}

bool File::check_size(const string &path, unsigned int min_size) {
    return get_size(path) >= min_size;
}

