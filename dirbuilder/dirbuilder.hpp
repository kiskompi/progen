#ifndef DIR_BUILDER
#define DIR_BUILDER
#include <string>

#include "../FTree/FTree.hpp"

class DirBuilder {
    // This class is responsible for building the directory structure and 
    // reading the structure files
private:
  std::string path_f;
  FTree* structure;

public:
  DirBuilder();
  DirBuilder(std::string structure_str);
  ~DirBuilder();

  // Creates the directory structure as it iterates through 'structure'
  void create_dirs(std::string path);
  // Reads a file to the 'structure' variable by calling the function of FTree 
  // responsible for this task
  std::vector<std::string> read_file(std::string fname);
  // Reads a the directory structure under path and writes it to a file
  void read_structure();
  // only calls structure.print()
  void print_structure();

  std::string path(){return path_f;}
};

#endif
