/*  
Name: Tony Nguyen, Chris Wu, Nathan Doan, Anh Ha  
Class: CPSC 223  
Date: April 30, 2025  
Assignment: Rivers Are Tree  
Description: Implementation of the Binary Tree to represent the Columbia River  
*/

#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <string>

Node::Node(const std::string& node, const std::string& type) {
    this->name = node;
    this->type = type;
    this->parent = nullptr;
    this->leftTrib = nullptr;
    this->rightTrib = nullptr;
    this->next = nullptr;
}

Node::Node(const std::string& node, const std::string& type, Node* parent, Node* leftTrib, Node* rightTrib, Node* next) {
    this->name = node;
    this->type = type;
    this->parent = parent;
    this->leftTrib = leftTrib;
    this->rightTrib = rightTrib;
    this->next = next;
}
    
Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    destroy(root);
    root = nullptr;
}

Node* Tree::findHelper(Node* node, const std::string& name) {
    if (!node) {
        return nullptr;
    }

    if (node->name == name) {
        return node;
    }

    Node* currNode = findHelper(node->leftTrib, name);
    if (currNode) {
        return currNode;
    } 

    currNode = findHelper(node->rightTrib, name);
    if (currNode) {
        return currNode;
    }

    return findHelper(node->next, name);
}

Node* Tree::findNode(const std::string& name) {
    return findHelper(root, name);
}

bool Tree::addFeatureOnBranch(const std::string& parentName, const std::string& childName, const std::string& type, bool left) {
    Node* currParent = findNode(parentName);
    if (!currParent) {
        return false;
    }

    if (left) {
        if (currParent->leftTrib) {
            return false;
        }
        currParent->leftTrib = new Node(childName, type);
        currParent->leftTrib->parent = currParent;
    }
    else {
        if (currParent->rightTrib) {
            return false;
        }
        currParent->rightTrib = new Node(childName, type);
        currParent->rightTrib->parent = currParent;
    }
    return true;
}

bool Tree::addFeatureOnSpine(const std::string& prevNode, const std::string& newNode, const std::string& type) {
    if (!root) {
        root = new Node(newNode, type);
        return true;
    }

    Node* currParent = findNode(prevNode);
    if (!currParent || currParent->next) {
        return false;
    }

    // currParent->next = new Node(newNode, type);
    // currParent->next->parent = currParent->parent;
    // return true;

    currParent->next = new Node(newNode, type);
    currParent->next->parent = currParent;
    return true;

}

void Tree::printHelper(Node* node, int indent) {
    if (!node) {
        return;
    }

    std::cout << std::string(indent*2, ' ') << node->name << " [" << node->type << "]\n";
    printHelper(node->leftTrib, indent+1);
    printHelper(node->rightTrib, indent+1);
    printHelper(node->next, indent);
}

void Tree::printTree() {
    if (!root) {
        std::cout << "<Empty Tree>\n";
    } 
    else {
        printHelper(root, 0);
    }
}

void Tree::traverseTree() {
    if (!root) {
        std::cout << "Tree is empty.\n";
        return;
    }

    Node* currNode = root;
    char choice;
    while (true) {
        std::cout << "\nCurrent: " << currNode->name << " [" << currNode->type << "]\n" << "Commands: \n\tL=left tributary \n\tR=right tributary \n\tP=parent  \n\tN=next  \n\tQ=quit\n> ";
        std::cin.clear();
        std::cin >> choice;
        if (!std::cin || choice == 'Q') {
            break;
        }
        if (choice == 'L' && currNode->leftTrib) {
            currNode = currNode->leftTrib;
        }
        else if (choice == 'R' && currNode->rightTrib) {
            currNode = currNode->rightTrib;
        }
        else if (choice == 'P' && currNode->parent) {
            currNode = currNode->parent;
        }
        else if (choice == 'N' && currNode->next) {
            currNode = currNode->next;
        }
        else {
            std::cout << "Invalid move.\n";
        }
    }
}

void Tree::destroy(Node* node) {
    if (!node) {
        return;
    }

    destroy(node->leftTrib);
    destroy(node->rightTrib);
    destroy(node->next);
    delete node;
}

// save: helper function to serialize the tree to a binary file
// I consulted LLM models to help with this process
void Tree::saveHelper(std::ofstream& out, Node* node) {
    char flag = 1;
    if (!node) {
        flag = 0;
    }
    out.write(&flag, sizeof(flag));
    if (!node) {
        return;
    }

    size_t nameLen = node->name.size();
    out.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    out.write(node->name.data(), nameLen);

    size_t typeLen = node->type.size();
    out.write(reinterpret_cast<char*>(&typeLen), sizeof(typeLen));
    out.write(node->type.data(), typeLen);

    saveHelper(out, node->leftTrib);
    saveHelper(out, node->rightTrib);
    saveHelper(out, node->next);
}

void Tree::save(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    saveHelper(out, root);
    out.close();
}

Node* Tree::loadHelper(std::ifstream& in, Node* parent) {
    char flag;
    if (!in.read(&flag, sizeof(flag)) || flag == 0) {
        return nullptr;
    }

    size_t nameLen;
    in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    std::string name(nameLen, '\0');
    in.read(&name[0], nameLen);

    size_t typeLen;
    in.read(reinterpret_cast<char*>(&typeLen), sizeof(typeLen));
    std::string type(typeLen, '\0');
    in.read(&type[0], typeLen);


    Node* node = new Node(name, type, parent, loadHelper(in, node), loadHelper(in, node), loadHelper(in, parent));
    return node;
}

void Tree::load(const std::string& filename)
{
    destroy(root);
    root = nullptr;

    std::ifstream in(filename, std::ios::binary);
    root = loadHelper(in, nullptr);
    in.close();
}
