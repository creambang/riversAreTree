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
#include <limits>

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
        if (prevNode.empty()) {
            root = new Node(newNode, type);
            return true;
        }
        return false;
    }

    Node* currParent = findNode(prevNode);
    if (!currParent || currParent->next) {
        return false;
    }

    currParent->next = new Node(newNode, type);
    currParent->next->parent = currParent;
    return true;
}

void Tree::printHelper(Node* node, int indent, bool isSpine) {
    if (!node) {
        return;
    }

    std::string position;
    if (node->parent == nullptr) {
        position = "Root";
    } else if (node->parent->leftTrib == node) {
        position = "Left";
    } else if (node->parent->rightTrib == node) {
        position = "Right";
    } else {
        position = "On Spine";
    }

    // Print the current node
    if (isSpine) {
        // Spine nodes are printed in the "centered" column without "Position: "
        std::cout << std::string(20, ' ') << node->name << " [Type: " << node->type << "]\n";
    } else if (node->parent && node->parent->leftTrib == node) {
        // Left tributaries cascade visually to the left
        std::cout << std::string(indent * 2, ' ') << node->name << " [Position: " << position << ", Type: " << node->type << "]\n";
    } else if (node->parent && node->parent->rightTrib == node) {
        // Right tributaries cascade visually to the right
        std::cout << std::string(20 + indent * 2, ' ') << node->name << " [Position: " << position << ", Type: " << node->type << "]\n";
    }

    // Recursively print left and right tributaries
    printHelper(node->leftTrib, indent + 1, false);
    printHelper(node->rightTrib, indent + 1, false);

    // Recursively print the next spine node
    printHelper(node->next, indent, true);
}

void Tree::printTree() {
    if (!root) {
        std::cout << "<Empty Tree>\n";
    } else {
        printHelper(root, 0, true); // Start with the root as a spine node
    }
}

Node* Tree::findPrevOnSpineHelper(Node* node, Node* target) {
    if (!node) {
        return nullptr;
    }
    if (node->next == target) {
        return node;
    }
    Node* found = findPrevOnSpineHelper(node->leftTrib, target);
    if (found) {
        return found;
    }
    found = findPrevOnSpineHelper(node->rightTrib, target);
    if (found) {
        return found;
    }
    return findPrevOnSpineHelper(node->next, target);
}

Node* Tree::findPrevOnSpine(Node* target) {
    return findPrevOnSpineHelper(root, target);
}

void Tree::traverseTree() {
    if (!root) {
        std::cout << "Tree is empty.\n";
        return;
    }

    Node* currNode = root;
    char choice;

    while (true) {
        std::cout << "\nCurrent: " << currNode->name
                  << " [" << currNode->type << "]\n"
                  << "Commands:\n"
                  << "\tL = left tributary\n"
                  << "\tR = right tributary\n"
                  << "\tP = parent\n"
                  << "\tN = next on spine\n"
                  << "\tB = back\n"
                  << "\tA = add feature here\n"
                  << "\tS = show tree\n"
                  << "\tQ = quit\n"
                  << "> ";
        std::cin.clear();
        std::cin >> choice;

        if (!std::cin || choice == 'Q') {
            break;
        }
        else if (choice == 'L' && currNode->leftTrib) {
            currNode = currNode->leftTrib;
        }
        else if (choice == 'R' && currNode->rightTrib) {
            currNode = currNode->rightTrib;
        }
        else if (choice == 'P' && currNode->parent) {
            currNode = currNode->parent;
        }
        else if (choice == 'S') {
            printTree();
        }
        else if (choice == 'N' && currNode->next) {
            currNode = currNode->next;
        }
        else if (choice == 'B') {
            Node* prev = findPrevOnSpine(currNode);
            if (!prev && currNode->parent) {
                prev = currNode->parent;
            }
            if (prev) {
                currNode = prev;
            }
            else {
                std::cout << "  -- no previous node\n";
            }
        }
        else if (choice == 'A') {
            char addChoice;
            std::cout << "Add (B)ranch or (S)pine? ";
            std::cin >> addChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (addChoice == 'B') {
                std::string childName, type;
                char dir;
                std::cout << "  Enter branch name: ";
                std::getline(std::cin, childName);
                std::cout << "  Enter type: ";
                std::getline(std::cin, type);
                std::cout << "  Left or Right (L/R)? ";
                std::cin >> dir;

                bool ok = addFeatureOnBranch(currNode->name, childName, type, (dir == 'L'));
                std::cout << (ok
                              ? "  Branch added.\n"
                              : "  Failed to add branch.\n");
            }
            else if (addChoice == 'S') {
                std::string newName, type;
                std::cout << "  Enter spine feature name: ";
                std::getline(std::cin, newName);
                std::cout << "  Enter type: ";
                std::getline(std::cin, type);

                bool ok = addFeatureOnSpine(currNode->name, newName, type);
                std::cout << (ok
                              ? "  Spine feature added.\n"
                              : "  Failed to add spine feature.\n");
            }
            else {
                std::cout << "  Invalid add option.\n";
            }
        }
        else {
            std::cout << "Invalid command.\n";
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

void Tree::saveHelper(std::ofstream& out, Node* node) {
    char flag = node ? 1 : 0;
    out.write(&flag, sizeof(flag));
    if (!node) {
        return;
    }

    size_t len = node->name.size();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(node->name.data(), len);

    len = node->type.size();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(node->type.data(), len);

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
    char flag = 0;
    if (!in.read(&flag, sizeof(flag)) || flag == 0) {
        return nullptr;
    }

    size_t len = 0;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string name(len, '\0');
    in.read(&name[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string type(len, '\0');
    in.read(&type[0], len);

    Node* node = new Node(name, type);
    node->parent = parent;

    node->leftTrib = loadHelper(in, node);
    node->rightTrib = loadHelper(in, node);
    node->next = loadHelper(in, parent);

    return node;
}

void Tree::load(const std::string& filename) {
    destroy(root);
    root = nullptr;

    std::ifstream in(filename, std::ios::binary);
    root = loadHelper(in, nullptr);
    in.close();
}
