#include <iostream>
#include <string>

class Node{
    private:
        std::string name;
        std::string treeType;
        std::string feature;
        // auto ifBranch;
        bool exit;
        Node* left;
        Node* right;

        // Constructor
        Node(std::string name, std::string treeType, std::string feature, bool exit)
        : name(name), treeType(treeType), feature(feature), exit(exit), left(nullptr), right(nullptr) {}
};

class BinaryTree{

};

int main() {
    BinaryTree tree;
    

}
