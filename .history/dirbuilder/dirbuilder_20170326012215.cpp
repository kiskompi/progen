#include "dirbuilder.hpp"
#include <fstream>
#include <iostream>

extern const std::string DEFAULT_STRUCTURE;

DirBuilder::DirBuilder()
{
    structure = std::make_shared<FTree>(FTree());
}

DirBuilder::DirBuilder(std::string const fname_): fname(fname_)
{
    structure = std::make_shared<FTree>(FTree());
    structure->build(read_file(fname));
}
DirBuilder::~DirBuilder()
{
    //TODO DirBuilder destructor, valamiért double delete
    //delete structure;
}

void DirBuilder::create_dirs()
{
    structure->create_dirs();
}

std::vector<std::string> DirBuilder::read_file(std::string const fname)
{
    std::ifstream myfile (fname);
    if (myfile.is_open()) {
        std::string line;
        std::vector<std::string> content = std::vector<std::string>();
        while ( getline (myfile,line) ) {
            content.push_back(line);
        }
        return content;
        myfile.close();
    } else throw("Unable to open file");
}

void DirBuilder::read_structure()
{
    /// Reads an existing file structure and writes it into a .str file
    //TODO reading dir sructure, str-ify it and write it to file
}

void DirBuilder::print_structure()
{
    structure->print();
}

void DirBuilder::set_path(std::string const path_)
{
    this->path = path_;
    structure->set_path(path);
}

void DirBuilder::create_dirs_with_path(std::string const path_)
{
    set_path(path_);
    create_dirs();
    std::cout<<"Structure created\n";
}