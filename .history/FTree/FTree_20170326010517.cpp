#include "FTree.hpp"
#include "../Exceptions/InvalidStructureException.hpp"

#if defined(_WIN64)
/* Microsoft Windows (64-bit). ------------------------------ */
const std::string SEPTOR = "\\";
#elif defined(_WIN32)
/* Microsoft Windows (32-bit). ------------------------------ */
const std::string SEPTOR = "\\";
#else
/* Any systems with '/' separators. ------------------------- */
const std::string SEPTOR = "/";
#endif

#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>


//================================= FTree::Folder methods ==========================================//


FTree::Folder::Folder()
    :depth(0),path("."),parent(nullptr)
{
    std::string tmp = "aaa";
    std::copy(tmp.begin(), tmp.end(), this->perm.data()); 
}

FTree::Folder::Folder(Folder const &f)
    :depth(f.depth),path(f.path),parent(f.parent), perm(f.perm)
{
}

FTree::Folder::Folder(std::shared_ptr<Folder> parent_, std::string p)
    :depth(0),path(p),parent(parent_)
{
    std::string tmp = "aaa";
    std::copy(tmp.begin(), tmp.end(), this->perm.data());
}

FTree::Folder::Folder(std::shared_ptr<Folder> parent_, std::string path_, int depth_, std::string perm_)
    :depth(depth_),path(path_),parent(parent_)
{
    std::copy(perm_.begin(), perm_.end(), this->perm.data());
}

FTree::Folder::~Folder()
{
    // delete parent;
}

//================================= FTree static methods ===================================//

std::string FTree::stack_to_string(std::stack<std::string> string_stack)
{
    std::string str;
    while(!string_stack.empty()) {
        str.insert(0,string_stack.top());
        string_stack.pop();
    }
    return str;
}


//================================= FTree methods ==========================================//

FTree::FTree()
    :root(Folder()), current(std::make_shared<Folder>(root))
{
}


FTree::~FTree()
{
}

void FTree::create_dirs(){
    create_dirs(std::make_shared<Folder>(root));
}

void FTree::create_dirs(std::shared_ptr<Folder> act)
{
    std::string full_path;
    if (act->depth == 0) {
        full_path = root.path+SEPTOR;
    } else {
        full_path = root.path+SEPTOR+act->path;
    }
    
    // FIXME childs is always empty!
    boost::filesystem::create_directory(boost::filesystem::path(full_path));
    std::cout<<"Create - Current: "<<act->path<<std::endl;
    std::cout<<full_path<<" created\n";

    if (!act->childs.empty()) {
        std::cout<<"child not empty "<<act->childs.size()<<"\n";
        for(int i = 0; i<act->childs.size(); ++i) {
            // TODO generic function should be passed
            create_dirs(std::make_shared<Folder>(act->childs.at(i)));
        }
    }
}


void FTree::add_child(Folder const &add_this)
{
    // std::cout<<"ADDED: "<<add_this.path<<" to "<<current->path<<std::endl;
    current->childs.push_back(add_this);
    for (Folder& i: current->childs) std::cout<<"Add_child - Current: "<<current->path<<" \t\t\t\t|--: "<<i.path<<std::endl;
    current->childs.at(current->childs.size()-1);
}

void FTree::build(std::vector<std::string> content)
{
    std::string line;
    int prev_depth = -1;
    size_t checker = 0;
    // végigmegy a sorokon, minden sorban létrehozza a szükséges változókat és kibányássza a név#perm-et és a levelt. Berakja a talált tuple-t a vectorba.
    std::stack<std::string> path_stack;

    for (auto const &line : content) {
        int depth = 0;
        std::string name_with_perm = "";
        int name_start = 0;
        int name_start_in = 0;

        while ((name_start_in = line.find("|--", name_start_in)) != std::string::npos) {
            ++depth;
            name_start_in = name_start_in + 3; // length of |--
            name_start = name_start_in;
        }

        name_with_perm = line.substr(name_start, line.length()); // a végéig olvassa, permissionökkel együtt
        try {
            if (name_with_perm.empty()) {
                throw InvalidStructureException();
            }
        } catch (InvalidStructureException ex) {
            std::cerr<<ex.what()<<std::endl;
            exit;
        }

        std::string name = "";
        std::string perm = "";

        if (name_with_perm.find('#') != std::string::npos) {
            name = name_with_perm.substr(0,name_with_perm.find('#'));
            perm = name_with_perm.substr(name_with_perm.find('#'));
        } else {
            name = name_with_perm;
            perm = "---";
        }
        name.append(SEPTOR);
        try {
            if(depth == prev_depth + 1){
                // structure creation working, folder creaton doesnt
                path_stack.push(name);
                if (!current->childs.empty()) 
                    current = std::make_shared<FTree::Folder>(current->childs.at(current->childs.size()-1));
                Folder folder_tmp(current, FTree::stack_to_string(path_stack), depth, perm);
                add_child(folder_tmp);
            } else if (depth == prev_depth) {
                path_stack.pop();
                path_stack.push(name);
                Folder folder_tmp(current, FTree::stack_to_string(path_stack), depth, perm);
                add_child(folder_tmp);
            } else if (depth > prev_depth + 1) {
                throw InvalidStructureException();
            } else {
                for (int i = 0; i < prev_depth - depth ; ++i){
                    current = current->parent;
                    path_stack.pop();
                }
                path_stack.pop();
                path_stack.push(name);
                Folder folder_tmp(current, FTree::stack_to_string(path_stack), depth, perm);
                add_child(folder_tmp);
            }
        } catch ( InvalidStructureException ex) {
            std::cerr<<"Progen exited with "<<ex.what()<<std::endl;
            exit;
        }
        prev_depth = depth;
    }
}

void FTree::print()
{
    explore(print_node);
}

void FTree::print_node()
{
    //TODO Non-static method, prints current node
    std::cout<<"node\n";
}

void FTree::explore(void (*func)())
{
    (*func)();

    for (int i = 0; i < current->childs.size(); ++i) std::cout<<current->childs[i].path<<std::endl;

    std::cout<<"Path to directory:"<<current->path;
    if (root.childs.empty()) return;
    current = std::make_shared<Folder>(FTree::Folder(root));
    for(int i = 0; i<root.childs.size(); ++i) {
        Folder &tmp = (current->childs[i]);
        this->explore(func, tmp);
    }
}

void FTree::explore(void (*func)(), FTree::Folder folder)
{
    (*func)();
    if (folder.childs.empty()) return;
    current = std::make_shared<Folder>(FTree::Folder(folder));
    for(int i = 0; i<root.childs.size(); ++i) {
        Folder &tmp = (current->childs[i]);
        this->explore(func, tmp);
    }
}

void FTree::set_path(std::string path_)
{
    root.path = path_;
}
