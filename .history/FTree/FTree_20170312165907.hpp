#ifndef FTREE
#define FTREE

#include <vector>
#include <string>
#include <array>
#include <functional>
#include <stack>
#include <memory>
class FTree {
/// In-memory data structure for storing folder structures. Built for progen.


    struct Folder {
        /// Nodes of the tree representing individual folders.
        size_t depth;                   ///< indicates the level of the tree this node is in. equals to: num_of_ancestors + 1
        std::string path;               ///< the path of the folder in foo/bar/baz style, relative to the tree root
        std::vector<Folder> childs;     ///< if empty, the node is a leaf
        std::array<char,3> perm;        ///< chmod permissions for the folder. if no file read, all folders have the same. files can specify it folder by folder
        std::shared_ptr<Folder> parent;

        Folder();
        Folder(Folder const &);
        Folder(std::shared_ptr<Folder>, std::string);
        Folder(std::shared_ptr<Folder>, std::string, int depth, std::string perm);
        ~Folder();
    };

    Folder root;                                        ///< if path is given, it is given to root so its path is not . anymore
    std::shared_ptr<Folder> current;                    ///< pointer to the currently (or last) used node

    /// creates a new Folder and puts it into the 'current' node's' 'childs' vector
    void add_child(Folder const &add_this);

    /// sets the 'current' pointer to its parent node
    void to_parent_folder() const;

    /// prints current the node in .str style but without the permissions.
    // with-perms may be implementad later
    static void print_node();

    /// This function iterates through the nodes of the tree in a depth-first
    /// manner and executes a passed function at every iteration.
    void explore(void (*to_execute)() );

    /// This function iterates through the nodes of the tree in a depth-first
    /// manner and executes a passed function at every iteration.
    /// \param Folder to_ex_param the parameter of the to_execute function
    void explore(void (*to_execute)(), FTree::Folder to_ex_param);

    /// This function iterates through a subtree of the tree.
    ///  \param The starting node of the depth-first exploration. The function will explore its subtrees
    void create_dirs(std::shared_ptr<Folder>);

public:
    FTree();
    FTree(char perms[3]);
    ~FTree();

    /// This function iterates through the tree and calls the boost create_directory
    /// function at every iteration to the current path. The initial call is parameterless
    /// and sets the current to the root.
    void create_dirs();

    /// Prints the structure to the output by calliny the explore function with the print_node() function as parameter
    void print();

    /// Build the structure of the tree based on a ultiline .str style string.
    /// \param dotstr_content is the .str style string the structure is built upon
    void build_structure(std::vector<std::string> dotstr_content);

    /// Sets the path of the 'root' node to a given path.
    void set_path(std::string);

    /// Builds a string of a stack
    static std::string stack_to_string(std::stack<std::string> string_stack);
};

#endif
