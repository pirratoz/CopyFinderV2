//
// Created by pirratoz on 30.09.23.
//

#include <experimental/filesystem>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "Controller.h"
#include "../utils/Dir.h"
#include "../utils/File.h"


namespace fs = std::experimental::filesystem;


void Controller::handle_folders(){
    while (!folders.empty()){
        string path = folders.front();
        folders.pop();
        if (!Dir::is_exists(path)) continue;
        if (!Dir::is_dir(path)) continue;
        if (!Dir::find_epath(path, epath)) continue;
        collect_files(path);
    }
}

void Controller::collect_files(const string &path) {
    for (auto &&entry : fs::directory_iterator(path)){
        if (Dir::is_dir((string &) entry.path())) {
            if (check_nested_folders) folders.push(entry.path());
            continue;
        }

        if (!File::check_size((string &) entry.path(), file_size_min)) continue;
        if (!File::find_mask((string &) entry.path(), masks)) continue;

        add_found_file((string &) entry.path(), File::get_size((string &) entry.path()));
    }
}

void Controller::add_found_file(const string &path, unsigned int file_size) {
    if (files.find(file_size) == files.end()) files[file_size] = std::list<string> { path };
    else files[file_size].push_front(path);
}

Controller::Controller(QStringList &folders, QStringList &masks, QStringList &epath, bool check_nested_folders,
                       unsigned file_size_min, unsigned block_size) {
    for (const QString& _folder : folders)
        this->folders.push(_folder.toStdString());
    for (const QString& _mask : masks)
        this->masks.push_back(_mask.toStdString());
    for (const QString& _epath : epath)
        this->epath.push_back(_epath.toStdString());
    folders.clear(); masks.clear(); epath.clear();
    this->check_nested_folders = check_nested_folders;
    this->file_size_min = file_size_min;
    this->block_size = block_size;
}
