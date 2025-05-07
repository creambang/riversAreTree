#ifndef RIVERTREE_HPP
#define RIVERTREE_HPP

#include <iostream>
#include <string>

class Node{
    public:
        std::string name;
        std::string treeType; // Tree type can be "Spine", "left", or "right"
        std::string feature;
        // auto ifBranch() -> bool { return !exit; } // Check if the node is a branch
        bool exit;
        Node* left;
        Node* right;
        Node* next;
        Node* prev;

        // Constructor
        Node(std::string name, std::string treeType = "Spine", std::string feature = "", bool exit = false);
};

class DoublyLinkedList{
    private:       
        Node* head;
        Node* tail;

    public:
        DoublyLinkedList();
        ~DoublyLinkedList();
        void addNode(std::string name, std::string feature, bool exit = false, std::string treeType = "Spine", 
            std::string leftName = "", std::string rightName = "");
        // void addNode(std::string name, std::string feature, bool exit);
        void display();
        void searchNode(std::string name);
        void searchRoute(std::string startName, std::string endName = "");
};

#endif