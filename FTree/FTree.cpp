#include <fstream>
#include <sstream>
#include <tuple>
#include <iostream>
#include <cstring>

#include "FTree.hpp"
#include "../Heap/Heap.hpp"

FTree::FTree()
{
    //TODO FTree default constructor
    root.depth = 0;
    strncpy(root.perm, "aaa\0", sizeof(root.perm));
    current = &root;
}
FTree::FTree(std::vector<std::string> file)
{
    //TODO FTree string constructor.
    // the algorithm to build the structure with add children
    stringified = str_to_string(file);
    root.depth = 0; 
    strncpy(root.perm, "aaa\0", sizeof(root.perm));
    current = &root;
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
    
    if (this->root.childs.empty()) return;
    for(int i = 0; i<root.childs.size();++i){
        //FIXME generic function should be passed
        Folder &tmp = (root.childs[i]);
        this->explore(FTree::print_node, tmp);
    }
}

void FTree::explore(void (*func)(), FTree::Folder folder)
{
    /// Explores the tree and calls the function for every node
    // TODO recursive explore algorithm and function call

    (*func)();
    if (folder.childs.empty()) return;
    current = &folder;
    print_node(current);
    for(int i = 0; i<root.childs.size();++i){
        Folder &tmp = (current->childs[i]);
        this->explore(FTree::print_node, tmp);
    }
}

void FTree::add_child(Folder folder)
{
    folder.childs.push_back(Folder());
}



std::string FTree::str_to_string(std::vector<std::string> content)
{
    //TODO [a[b]]-ify a file content passed as a string

    std::string stringified;
    std::string line;
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

        Folder folder_tmp;
        folder_tmp.depth = depth; 
        //FIXME a path-t kell berakni a name helyett!!
        folder_tmp.name=name;
        strncpy(folder_tmp.perm, perm.c_str(), sizeof(folder_tmp.perm));
        folder_tmp.perm[sizeof(folder_tmp.perm) - 1] = 0;

        add_child(folder_tmp);
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

void FTree::print_node(){std::cout<<"node\n";}

void FTree::print_node(Folder* f){
    //FIXME a path-t kell berakni a name helyett!!
    std::cout<<"Node name: "<<f->name<<std::endl;
    for (int i =0; i<f->childs.size();++i) std::cout<<" f->depth\n";
}
