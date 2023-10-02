//
// Created by pirratoz on 30.09.23.
//

#ifndef COPYFINDER_CONTROLLER_H
#define COPYFINDER_CONTROLLER_H

#include <QStringList>
#include <string>
#include <queue>
#include <list>
#include <map>

using std::string;
using std::queue;
using std::list;
using std::map;


class Controller {
private:
    queue<string> folders;
    map<unsigned, list<string>> files;
    list<string> masks;
    list<string> epath;
    bool check_nested_folders;
    unsigned file_size_min;
    unsigned block_size;
public:
    Controller(
            QStringList & folders,
            QStringList & masks,
            QStringList & epath,
            bool check_nested_folders,
            unsigned file_size_min,
            unsigned block_size
            );
private:
    void add_found_file(const string & path, unsigned file_size);
    void collect_files(const string & path);
public:
    void handle_folders();
};


#endif //COPYFINDER_CONTROLLER_H
