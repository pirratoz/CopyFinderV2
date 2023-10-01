//
// Created by pirratoz on 30.09.23.
//

#ifndef COPYFINDER_DIR_H
#define COPYFINDER_DIR_H


#include <string>
#include <list>

using std::string;
using std::list;


class Dir {
public:
    static bool is_dir(string & path);
    static bool is_exists(string & path);
    static bool find_epath(string & path, list<string> epaths);
};


#endif //COPYFINDER_DIR_H
