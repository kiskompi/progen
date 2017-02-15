#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "dirbuilder/dirbuilder.hpp"

namespace fs = boost::filesystem;
namespace po = boost::program_options;

const std::string DEFAULT_STRUCTURE = "[name1[name2[name3],name5[name6],name4]name7]";

int main(int argc, char** argv) {
    std::string path;
    std::string file_name;
    bool cmake;
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("path,P", po::value<std::string>(&path), "Set project path")
            ("cmake,C", po::value<bool>(&cmake) -> default_value(true), "Creates cMake.txt if true")
            ("file,F", po::value<std::string>(&path), "Set file to read, must be in path directory! If not set, default structure will be built.")
            ;
            
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    // már deklarációnál is SEGFAULT-ot dob
    DirBuilder db;
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    if (vm.count("file")) {
        // Ha ezt nem kommentelem ki, Memory map-et is dob. Ha igen, akkor csak segfault-ol (ha db deklarálva van).
        std::string fname = vm["file"].as<std::string>();
        //db = DirBuilder(fname);
        //db.print_structure();
    } else {
        //db = DirBuilder();
    }
    if (vm.count("path")) {
        std::cout << "Path to project is:" << vm["path"].as<std::string>() << "\n";
        //db.create_dirs(path);
    } else {
        std::cout << "Path was not set.\n";
    }
    if (vm.count("cmake")) {
        std::cout << "cMake is:" << vm["cmake"].as<bool>() << "\n";
    } else {
        std::cout << "cMake was not set.\n";
    }
}
