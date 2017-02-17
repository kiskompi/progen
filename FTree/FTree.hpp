#ifndef FTREE
#define FTREE

#include <vector>
#include <string>

class FTree {
/// In-memory data structure for storing folder structures. Built for progen.


    class Folder {
        /// Nodes of the tree representing indivisual folders.
        public:
            size_t depth;
            std::string path;               /// the path of the folder in foo/bar/baz style, relative to the tree root
            std::vector<Folder> childs;
            char perm[4] = "aaa";                   /// chmod permissions for the folder. if no file read, all folders have the same. files can specify it folder by folder
            Folder* parent;

            Folder();
            Folder(Folder*, std::string);
            ~Folder();

            void add_child();
    };

    Folder root;
    Folder* current;
    std::string stringified;

    // creates a new Folder* and puts it into the 'current' node's' childs vector
    void add_child(Folder add_this);
    // sets the 'current' pointer to the parent of the current 'current' 
    void to_parent_folder();

    // prints the node in .str style but without the permissions. --with-perms may be implementad later
    static void print_node(Folder*);
    // prints the 'current' node
    static void print_node();

    // have to get a function to call at every node! this can be a mkdir function if needed
    void explore(void (*func)());
    void explore(void (*func)(), Folder);

public:
    FTree();
    FTree(char perms[3]);

    void create_dirs();
    void create_dirs(Folder*);

    std::string get_current(){return current->path;}

    ~FTree();

    // Prints the structure to the output by callind the explore function with a print_node() function as parameter
    void print();
    // translates the incoming .str file to an inline [a[b]] style. gets the file content as std::string
    std::string build_structure(std::vector<std::string> f);

    void set_path(std::string);

};

#endif
