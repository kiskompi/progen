#ifndef DIR_BUILDER
#define DIR_BUILDER
#include <string>
#include <boost/filesystem.hpp>

#include "../FTree/FTree.hpp"

class DirBuilder {
    // This class is responsible for building the directory structure and 
    // reading the structure files
private:
  std::string fname;
  FTree* structure;
  std::string path;

public:
  DirBuilder();
  DirBuilder(std::string structure_str);
  ~DirBuilder();

  void set_path(std::string);
  // Creates the directory structure as it iterates through 'structure'
  void create_dirs();
  // Reads a file to the 'structure' variable by calling the function of FTree 
  // responsible for this task
  static std::vector<std::string> read_file(std::string fname);
  // Reads a the directory structure under path and writes it to a file
  void read_structure();
  // only calls structure.print()
  void print_structure();

  void create_dirs_with_path(std::string);

};

#endif
