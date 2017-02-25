#include "FTree.hpp"

#if defined(_WIN64)
	/* Microsoft Windows (64-bit). ------------------------------ */
    const std::string SEPTOR = "\\";    
#elif defined(_WIN32)
	/* Microsoft Windows (32-bit). ------------------------------ */
    const std::string SEPTOR = "\\";
#else
    const std::string SEPTOR = "/";
#endif

#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>  
#include <boost/filesystem.hpp>


//================================= FTree::Folder methods ==========================================//


FTree::Folder::Folder()
    :depth(0),path("."),parent(nullptr)
{
    std::string tmp = "aaa";
    std::copy(tmp.begin(), tmp.end(), this->perm.data());                  /// chmod permissions for the folder. if no file read, all folders have the same. files can specify it folder by folder
}

FTree::Folder::Folder(Folder* parent_, std::string p)
    :depth(0),path(p),parent(parent_)
{
    std::string tmp = "aaa";
    std::copy(tmp.begin(), tmp.end(), this->perm.data());
}

FTree::Folder::Folder(Folder* parent_, std::string p, int depth, std::string perm_in)
    :depth(depth),path(p),parent(parent_)
{
    std::copy(perm_in.begin(), perm_in.end(), this->perm.data());
}

FTree::Folder::~Folder(){

}

//================================= FTree static methods ===================================//

std::string stack_to_string(std::stack<std::string> string_stack){
    std::string str;
    while(!string_stack.empty()){
        str.insert(0,string_stack.top());
        string_stack.pop();
    }
    return str;
}


//================================= FTree methods ==========================================//

FTree::FTree()
{
    root = Folder();
    current = &root;
}



FTree::~FTree()
{
    delete current;
}

void FTree::create_dirs(){
    if (root.path!="."){
        boost::filesystem::create_directory(boost::filesystem::path(root.path));
    }
    create_dirs(&root);
}

void FTree::create_dirs(Folder* f){

    if (f->childs.empty()) return;
    for(int i = 0; i<root.childs.size();++i){
        //FIXME generic function should be passed
        current = &(f->childs[i]);
        std::string full_path = root.path+SEPTOR+current->path;
        boost::filesystem::create_directory(boost::filesystem::path(full_path));
        this->create_dirs(current);
    }
}

void FTree::add_child(Folder add_this)
{
    current->childs.push_back(add_this);
}

void FTree::build_structure(std::vector<std::string> content)
{
    /// Felépíti a fát a beolvasott fájl alapján

    std::string line;
    int prev_depth = -1;
    size_t checker = 0;
    // végigmegy a sorokon, minden sorban létrehozza a szükséges változókat és kibányássza a név#perm-et és a levelt. Berakja a talált tuple-t a vectorba.
    std::stack<std::string> path_stack;

    for (auto const &line : content)
    {
        int depth = 0;
        std::string name_with_perm = "";
        int name_start = 0;
        int name_start_in = 0;

        while ((name_start_in = line.find("|--", name_start_in)) != std::string::npos)
        {
            ++depth;
            name_start_in = name_start_in + 3; // length of |--
            name_start = name_start_in;
        }
        
        name_with_perm = line.substr(name_start, line.length()); // a végéig olvassa, permissionökkel együtt
        if (name_with_perm.empty()){
            std::cerr<<"No folder name!\n";
            exit;
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
        name.append(SEPTOR);
        if(depth > prev_depth) 
            path_stack.push(name);
        else if (depth == prev_depth){
            path_stack.pop();
            path_stack.push(name);
        } else {
            for (int i = 0; i<prev_depth-depth+1; ++i)
                path_stack.pop();
            path_stack.push(name);
        }

        Folder folder_tmp(current, stack_to_string(path_stack), depth, perm);
        folder_tmp.depth = depth; 

        add_child(folder_tmp);
        prev_depth = depth;
    }
    print();
}

void FTree::print()
{
    std::cout<<"PRINT:\n";
    using namespace std::placeholders;
    std::function<void(Folder&)> f = std::bind(static_cast<void(FTree::*)(Folder&)>(&FTree::print_node, this, _1));

    explore(f);
}

void FTree::print_node(Folder &f){
    std::cout<<f.path<<std::endl;
}

void FTree::explore(std::function<void(Folder&)> func)
{
    /// Explores the tree and calls the function for every node
    // TODO recursive explore algorithm and function call
    current = &root;
    func(root);
    if (root.childs.empty()) return;
    for(int i = 0; i<root.childs.size();++i){
        this->explore(func, (current->childs[i]));
    }
}


void FTree::explore(std::function<void(Folder&)> func, FTree::Folder folder)
{
    /// Explores the tree and calls the function for every node
    // TODO recursive explore algorithm and function call
    func(folder);
    if (folder.childs.empty()) return;
    for(int i = 0; i<folder.childs.size();++i){
        this->explore(func, (folder.childs[i]));
    }
}

void FTree::set_path(std::string path_){
    root.path = path_;
}
