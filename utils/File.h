//
// Created by pirratoz on 30.09.23.
//

#ifndef COPYFINDER_FILE_H
#define COPYFINDER_FILE_H


#include <string>
#include <list>


using std::string;
using std::list;


class File {
public:
    static string get_name(const string& path);
    static unsigned get_size(const string& path);
    static bool find_mask(const string& path, const list<string>& masks);
    static bool check_size(const string& path, unsigned min_size);
};


#endif //COPYFINDER_FILE_H
