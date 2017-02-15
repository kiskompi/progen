#include "dirbuilder.hpp"
#include <fstream>
#include <iostream>

extern const std::string DEFAULT_STRUCTURE;

DirBuilder::DirBuilder(){
  structure = new FTree();
}

DirBuilder::DirBuilder(std::string path): path_f(path){
  //TODO DirBuilder string constructor
  structure = new FTree(read_file(path_f));
}
DirBuilder::~DirBuilder(){
  //TODO DirBuilder destructor
  delete structure;
}

void DirBuilder::create_dirs(std::string path){
  structure->print();
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
    structure->print();
}
