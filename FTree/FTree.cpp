#include "FTree.hpp"
#include <fstream>
#include <sstream>
#include <tuple>
#include <iostream>
#include <cstring>

FTree::FTree()
{
    //TODO FTree default constructor
    root->depth = 0; 
    strncpy(root->perm, "aaa", sizeof(root->perm));
}
FTree::FTree(std::vector<std::string> file)
{
    //TODO FTree string constructor.
    // the algorithm to build the structure with add children
    stringified = str_to_string(file);
    root->depth = 0; 
    strncpy(root->perm, "aaa", sizeof(root->perm));
}

FTree::~FTree()
{
    //TODO FTree destructor
}

// have to get a function to call at every node! this can be a mkdir function if needed
void FTree::explore(void (*func)())
{
    /// Explores the tree and calls the function for every node
    // TODO recursive explore algorithm and function call
    func();
    if (!this->root->childs.empty()){
        for(auto const& subfolder: this->root->childs){
            explore(func, subfolder);
        }   
    } else return;
}

void FTree::explore(void (*func)(), Folder* folder)
{
    /// Explores the tree and calls the function for every node
    // TODO recursive explore algorithm and function call
    func();
    if (folder->childs.empty()) return;
    for(auto const& subfolder: folder->childs){
        explore(func, subfolder);
    }
}

void FTree::add_child(Folder *folder)
{
    folder->childs.push_back(new Folder());
}



std::string FTree::str_to_string(std::vector<std::string> content)
{
    //TODO [a[b]]-ify a file content passed as a string

    std::string stringified;
    std::string line;
    std::tuple<std::string, int> tuple;
    std::vector<Folder* > folders;
    int prev_depth = -1;
    size_t checker = 0;
    // végigmegy a sorokon, minden sorban létrehozza a szükséges változókat és kibányássza a név#perm-et és a levelt. Berakja a talált tuple-t a vectorba.

    for (auto const &line : content)
    {
        int depth = 0;
        std::string name_with_perm = "";
        int name_start = 0;
        int name_start_in = 0;

        while ((name_start_in = line.find("|--", name_start_in)) != std::string::npos)
        {
            ++depth;
            name_start_in = name_start_in + 2; // length of |--
            name_start = name_start_in;
        }
        
        name_with_perm = line.substr(name_start, line.length()); // a végéig olvassa, permissionökkel együtt
        if (name_with_perm.empty()){
            std::cerr<<"No folder name!\n";
            return "ERROR";
        }

        std::string name = "";
        std::string perm = "";

        if (name_with_perm.find('#') != std::string::npos){
            name = name_with_perm.substr(0,name_with_perm.find('#'));
            perm = name_with_perm.substr(name_with_perm.find('#'));
        } else {
            name = name_with_perm;
            perm = "---";
        }

        Folder* folder_tmp = new Folder;
        folder_tmp->depth = depth; 
        folder_tmp->childs = std::vector<Folder*>();
        strncpy(folder_tmp->perm, perm.c_str(), sizeof(folder_tmp->perm));
        folder_tmp->perm[sizeof(folder_tmp->perm) - 1] = 0;

        folders.push_back(folder_tmp);
/*
        int kul = prev_depth - depth;
        if (kul > 0)
        {
            // if current is more near to root than previous
            for (int k = 0; k < kul; ++k)
                stringified.append("]");
            stringified.append("," + name);
        }
        else if (kul == 0)
        {
            // if current is a sibling
            stringified.append("," + name);
        }
        else if (kul == -1)
        {
            // if current is a child of the previous
            stringified.append("[" + name);
        }
        else
            throw("Invalid folder structure");

        prev_depth = depth;*/
    }

    return stringified;
}

void FTree::print()
{
    //TODO FTree print()
    explore(print_node);
}

void FTree::print_node(){
    std::cout<<"NODE";
}
