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
        std::shared_ptr<Folder> parent; ///< pointer indicating the Folder whose 'childs' vector contains this Folder

        Folder();

        /// Simple copy constructor
        Folder(Folder const &);
        
        /// This constructor gets the parent Folder and the path of itself 
        /// \param std::shared_ptr<Folder> parent_ : the parent Folder of the to-be created Folder
        /// \param std::string path_ : the path of the to-be-created Folder
        Folder(std::shared_ptr<Folder> parent_, std::string path_);
        
        /// This constructor gets every data to set
        /// \param std::shared_ptr<Folder> parent_ : the parent Folder of the to-be created Folder
        /// \param std::string path_ : the path of the to-be-created Folder
        /// \param int depth_ : the depth of the Folder in the FTree
        /// \param std::string perm_ : the permissions assiciated to the Folder
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
    ///  \param Folder folder The starting node of the depth-first exploration. The function will explore its subtrees

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

    /// Builds the structure of the tree based on a .str style string.
    /// \param dotstr_content is the .str style string the structure is built upon
    void build(std::vector<std::string> dotstr_content);

    /// Sets the path of the 'root' node to a given path.
    void set_path(std::string new_path);

    /// Builds a single string from a stack of strings
    static std::string stack_to_string(std::stack<std::string> string_stack);
};

#endif
