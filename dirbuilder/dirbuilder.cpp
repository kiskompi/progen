#include "dirbuilder.hpp"
#include <fstream>
#include <iostream>

extern const std::string DEFAULT_STRUCTURE;

DirBuilder::DirBuilder(){
  structure = new FTree();
}

DirBuilder::DirBuilder(std::string fname_): fname(fname_){
  //TODO DirBuilder string constructor
  structure = new FTree();
  structure->build_structure(read_file(fname));
}
DirBuilder::~DirBuilder(){
  //TODO DirBuilder destructor, valamiért double delete
  //delete structure;
}

void DirBuilder::create_dirs(){
  /// létrehoz egy stringet path (dir1/dir2) formában a structure->currentből (vagy minden Foldernek kell egy path), és ebbe a path-ba létrehoz egy directory-t
  //std::function<bool(std::string)> creator = std::bind(&boost::filesystem::create_directory, structure->get_current());
  structure->create_dirs();
}

std::vector<std::string> DirBuilder::read_file(std::string fname){
  std::ifstream myfile (fname);
  if (myfile.is_open()){
    std::string line;
    std::vector<std::string> content = std::vector<std::string>();
    while ( getline (myfile,line) ) {
      content.push_back(line);
    }
    return content;
    //structure = new FTree(content);
    myfile.close();
  } else throw("Unable to open file");
}

void DirBuilder::read_structure(){
  /// Reads an existing file structure and writes it into a .str file
    //TODO reading dir sructure, str-ify it and write it to file
}
void DirBuilder::print_structure(){
  /// Prints the 'structure' to the terminal
    structure->print();
}

void DirBuilder::set_path(std::string path_){
    this->path = path_;
    structure->set_path(path);
}

void DirBuilder::create_dirs_with_path(std::string path_){
    set_path(path_);
    create_dirs();
}