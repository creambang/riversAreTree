/*  
Name: Tony Nguyen, Chris Wu, Nathan Doan, Anh Ha
Class: CPSC 223  
Date: April 30, 2025  
Assignment: Rivers Are Tree  
Description: Declaration of the Binary Tree to represent the Columbia River   
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <fstream>

class Node {
    public:
        std::string name;
        std::string type;
        Node* parent;
        Node* leftTrib; 
        Node* rightTrib;
        Node* next;

        Node(const std::string& node, const std::string& type);
        Node(const std::string& node, const std::string& type, Node* parent, Node* leftTrib, Node* rightTrib, Node* next = nullptr);
};

class Tree {
    private:
        Node* root;
        
    public:
        Tree();
        ~Tree();
        Node* findNode(const std::string& name);
        bool addFeatureOnBranch(const std::string& parentName, const std::string& childName, const std::string& type, bool left);
        bool addFeatureOnSpine(const std::string& prevNode, const std::string& newNode, const std::string& type);
        void printTree();
        void traverseTree();
        void save(const std::string& filename);
        void load(const std::string& filename);

        void destroy(Node* n);
        Node* findHelper(Node* node, const std::string& name);
        void printHelper(Node* node, int indent);
        void saveHelper(std::ofstream& out, Node* node);
        Node* loadHelper(std::ifstream& in, Node* parent);
};

#endif
