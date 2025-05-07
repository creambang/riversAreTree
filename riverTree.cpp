#include <iostream>
#include <string>
#include "riverTree.hpp"

// Constructor
Node::Node(std::string name, std::string treeType, std::string feature, bool exit) {
    this->name = name;
    this->treeType = treeType;
    this->feature = feature;
    this->exit = exit;
    this->left = nullptr;
    this->right = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {};


DoublyLinkedList::~DoublyLinkedList() {
    Node * currNode = head;
    Node * nextNode = nullptr;

    while (currNode != nullptr){
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}


void DoublyLinkedList::addNode(std::string name, std::string feature, bool exit, std::string treeType,
    std::string leftName, std::string rightName) {
    // Create a new node
    Node* newNode = new Node(name, treeType, feature, exit);

    // Set tributaries if provided
    if (!leftName.empty()) {
        newNode->left = new Node(leftName, "River");
    }
    if (!rightName.empty()) {
        newNode->right = new Node(rightName, "River");
    }

    // Add the new node to the doubly linked list
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}


// void DoublyLinkedList::addNode(std::string name, std::string feature, bool exit) {
//     addNode(name, feature, "No", "Spine", "", ""); // Default treeType to "Spine", exit to "No", and no tributaries);
// }


void DoublyLinkedList::display() {
    Node* current = head;
    int nodeNumber = 1; // Initialize a counter for numbering nodes
    while (current != nullptr) {
        std::cout << nodeNumber << ". " << current->name 
                    << ", Feature Type: " << current->feature 
                    << ", Exit: " << (current->exit ? "Yes" : "No") << std::endl;

        // Display tributaries if they exist
        if (current->left != nullptr || current->right != nullptr) {
            std::cout << " with tributaries: ";
            if (current->left != nullptr) std::cout << "Left -> " << current->left->name << " River;  ";
            if (current->right != nullptr) std::cout << "Right -> " << current->right->name << " River ";
        }
        std::cout << "\n" << std::endl;
        current = current->next;
        nodeNumber++; // Increment the counter
    }
}


void DoublyLinkedList::searchNode(std::string name) {
    Node* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            std::cout << "Found: " << current->name << ", Feature: " << current->feature << ", Exit: " << (current->exit ? "Yes" : "No") << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Node not found." << std::endl;
}


void DoublyLinkedList::searchRoute(std::string startName, std::string endName) {
    Node* current = head;
    int nodeNumber = 1; // Counter for numbering nodes

    // Find the starting node
    while (current != nullptr && current->name != startName) {
        current = current->next;
    }

    // If the starting node is not found
    if (current == nullptr) {
        std::cout << "Starting node \"" << startName << "\" not found." << std::endl;
        return;
    }

    // Iterate and display nodes from the starting node
    std::cout << "Displaying route starting from \"" << startName << "\"";
    if (!endName.empty()) {
        std::cout << " and ending at \"" << endName << "\"";
    }
    std::cout << ":" << std::endl;

    while (current != nullptr) {
        // Display the current node with a number
        std::cout << nodeNumber << ". "<< current->name << ", Feature: " << current->feature 
                    << ", Exit: " << (current->exit ? "Yes" : "No") << std::endl;

        // Increment the node counter
        nodeNumber++;

        // Display left and right tributaries if they exist
        if (current->left != nullptr || current->right != nullptr) {
            if (current->left != nullptr) {
                std::cout << "   " << nodeNumber << ". Left Tributary: " << current->left->name << std::endl;
                nodeNumber++;
            }
            if (current->right != nullptr) {
                std::cout << "   " << nodeNumber << ". Right Tributary: " << current->right->name << std::endl;
                nodeNumber++;
            }
        }

        // Stop if the current node matches the endName
        if (!endName.empty() && current->name == endName) {
            break;
        }

        current = current->next;
    }

    // If endName was specified but not found
    if (!endName.empty() && current == nullptr) {
        std::cout << "End node \"" << endName << "\" not found. Displayed up to the tail node." << std::endl;
    }
}
