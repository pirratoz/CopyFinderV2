//
// Created by pirratoz on 30.09.23.
//

#include <experimental/filesystem>

#include "Controller.h"
#include "../utils/Dir.h"
#include "../utils/File.h"
#include "../md5/md5.h"

using std::ifstream;

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
    this->start_comparing_files();
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
    this->block_memory = new char[block_size];
}

void Controller::start_comparing_files() {
    for (auto & pair : this->files){
        auto & paths = pair.second;
        while (true) {
            if (paths.empty() || paths.size() == 1) break;
            paths = this->find_identity_content(pair.first, paths);
        }
        paths.clear();
    }
}

list<string> Controller::find_identity_content(unsigned int size, list<string> paths) {
    list<string> not_identical_files;
    bool print_first_path = false;
    const unsigned count_files = paths.size() - 1;
    bool *equals = new bool[count_files];
    memset(equals, true, count_files);

    unsigned int count_iter = (size % this->block_size > 0) ?
                              (size / this->block_size) + 1 : size / this->block_size;

    string first_file_path = paths.front(); paths.pop_front();

    for (int i = 0; i < count_iter; ++i) {
        std::string hash = get_md5(first_file_path, i, size);
        int j = 0;
        for (auto path = paths.begin(); path != paths.end(); ++j, ++path){
            if (!equals[j]) continue;
            if (hash != get_md5(*path, i, size)) equals[j] = false;
        }
    }

    for (int i = 0; i < count_files; ++i){
        auto path = paths.front();
        paths.pop_front();
        if (equals[i]) qDebug() << path.c_str();
        else not_identical_files.push_back(path);
        print_first_path |= equals[i];
    }
    if (print_first_path) qDebug() << first_file_path.c_str() << "\n";

    delete[] equals;
    return not_identical_files;
}

string Controller::get_md5(string &path, int iter, unsigned int size) {
    unsigned offset = iter * block_size;
    memset(block_memory, 0, block_size);
    ifstream file(path, std::ios::binary);
    file.seekg(offset);
    if (offset > size) file.read(block_memory, (size - offset));
    else file.read(block_memory, block_size);
    file.close();
    return md5(block_memory);
}

Controller::~Controller() {
    delete[] block_memory;
}
