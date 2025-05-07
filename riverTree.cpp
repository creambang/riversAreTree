#include <iostream>
#include <string>

class Node{
    public:
        std::string name;
        std::string treeType; // Tree type can be "Spine", "left", or "right"
        std::string feature;
        auto ifBranch() -> bool { return !exit; } // Check if the node is a branch
        bool exit;
        Node* left;
        Node* right;
        Node* next;
        Node* prev;

        // Constructor
        Node(std::string name, std::string treeType = "Spine", std::string feature = "", bool exit = false) //treetype default to "Spine"
        : name(name), treeType(treeType), feature(feature), exit(exit), left(nullptr), right(nullptr) {}
};

class DoublyLinkedList{
    private:
        Node* head;
        Node* tail;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}

        // Original addNode with 6 parameters
        void addNode(std::string name, std::string treeType = "Spine", std::string feature = "", bool exit = false, 
                     std::string leftName = "", std::string rightName = "") {
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
        // Overloaded addNode with 2 parameters
        void addNode(std::string name, std::string feature, bool exit) {
            addNode(name, "Spine", feature, "No", "", ""); // Default treeType to "Spine", exit to "No", and no tributaries);
        }

        void display() {
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

        void searchNode(std::string name) {
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

        void searchRoute(std::string startName, std::string endName = "") {
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
};

int main() {
    DoublyLinkedList mainRiver;
    std::cout << "\nColumbia River Tree Structure: " << std::endl;
    mainRiver.addNode("Astoria", "", "City", false, "Youngs", "Grays");
    mainRiver.addNode("Rufus", "City");
    mainRiver.addNode("Wanapum", "Dam");
    mainRiver.addNode("Portland", "City");
    mainRiver.addNode("Cascade Locks", "City");
    mainRiver.addNode("Bonneville Dam", "Dam");
    mainRiver.addNode("The Dalles", "City");
    mainRiver.addNode("Rufus", "City");
    mainRiver.addNode("John Day", "Dam");
    mainRiver.addNode("Umatilla", "City");
    mainRiver.addNode("McNary", "Dam");
    mainRiver.addNode("Mattawa", "City");
    mainRiver.addNode("Priest Rapids", "Dam");
    mainRiver.addNode("Vantage", "City");
    mainRiver.addNode("Wanapum", "Dam");
    mainRiver.addNode("Wenatchee", "City");
    mainRiver.addNode("Rock Island", "Dam");
    mainRiver.addNode("Chelan County", "City");
    mainRiver.addNode("Rocky Reach", "Dam");
    mainRiver.addNode("Pateros", "City");
    mainRiver.addNode("Wells", "Dam");
    mainRiver.addNode("Bridgeport", "City");
    mainRiver.addNode("Chief Joseph", "Dam");
    mainRiver.addNode("Coulee City", "City");
    mainRiver.addNode("Grand Coulee", "Dam");
    mainRiver.addNode("Little Falls", "Dam");
    mainRiver.addNode("Long Lake", "Dam");
    mainRiver.addNode("Nine Mile Falls", "City");
    mainRiver.addNode("Monroe", "Dam");

    mainRiver.display();
    mainRiver.searchRoute("Astoria", "Portland"); // Example search for a node
}
