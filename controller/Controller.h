//
// Created by pirratoz on 30.09.23.
//

#ifndef COPYFINDER_CONTROLLER_H
#define COPYFINDER_CONTROLLER_H

#include <QStringList>
#include <QDebug>
#include <QString>

#include <string>
#include <cstring>
#include <queue>
#include <list>
#include <map>
#include <fstream>

using std::string;
using std::queue;
using std::list;
using std::map;
using std::memset;


class Controller {
private:
    queue<string> folders;
    map<unsigned, list<string>> files;
    list<string> masks;
    list<string> epath;
    bool check_nested_folders;
    unsigned file_size_min;
    unsigned block_size;
    char * block_memory;

public:
    Controller(
            QStringList & folders,
            QStringList & masks,
            QStringList & epath,
            bool check_nested_folders,
            unsigned file_size_min,
            unsigned block_size
            );
    ~Controller();
private:
    void add_found_file(const string & path, unsigned file_size);
    void collect_files(const string & path);
    void start_comparing_files();
    string get_md5(string & path, int iter, unsigned size);
    list<string> find_identity_content(unsigned size, list<string> paths);
public:
    void handle_folders();
};


#endif //COPYFINDER_CONTROLLER_H
