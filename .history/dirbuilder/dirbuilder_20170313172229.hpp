#ifndef DIR_BUILDER
#define DIR_BUILDER
#include <string>
#include <boost/filesystem.hpp>

#include "../FTree/FTree.hpp"

class DirBuilder {
    /// This class is responsible for building the directory structure and
    /// reading the structure files
private:
    std::string fname;                    ///< Tha name of the .str file which contains the description of the folder structure
    std::shared_ptr<FTree> structure;     ///< An FTree structure which represents the folder structure to be created
    std::string path;                     ///< The name of the folder in which the folder structure will be created. Can be an absoulte path.

    void set_path(std::string);

    /// Creates the directory structure as it iterates through 'structure' by calling structure->create_dirs().
    void create_dirs();

public:
    DirBuilder();
    DirBuilder(std::string structure_str);
    ~DirBuilder();

    /// Reads a file to the 'structure' variable by calling the function of FTree
    /// responsible for this task
    static std::vector<std::string> read_file(std::string fname);

    /// Reads a the directory structure under path and writes it to a file
    void read_structure();

    /// Prints the FTree structure in a .str style. This function only calls structure.print()
    void print_structure();

    /// Sets the path of the structure and creates it by calling create_dirs()
    void create_dirs_with_path(std::string);

};

#endif
