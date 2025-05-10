#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <cassert> 

int main() {
    // Example usage of the Tree class
    Tree river;
    river.addFeatureOnSpine("", "Lower Colombia", "Mouth");
    river.addFeatureOnBranch("Lower Colombia", "KENN River", "River", true);
    river.addFeatureOnBranch("KENN River", "Snake Trit", "Tributary", false);
    river.addFeatureOnBranch("Lower Colombia", "Willamette River", "River", false);
    
    // Add a chain of spine nodes
    river.addFeatureOnSpine("Lower Colombia", "Astoria", "City");
    river.addFeatureOnSpine("Astoria", "St. Helens", "City");
    river.addFeatureOnSpine("St. Helens", "Portland", "City");

    Node* temp = river.findNode("Snake Trit")->parent;
    std::cout << temp->name << std::endl;
    
    // Print the tree structure
    river.printTree();
    
    return 0;
}

// // Simple test framework
// #define ASSERT(condition, message) \
//     do { \
//         if (!(condition)) { \
//             std::cerr << "FAIL: " << message << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
//             return false; \
//         } \
//     } while (false)

// #define RUN_TEST(test) \
//     do { \
//         std::cout << "Running " << #test << "... "; \
//         if (test()) { \
//             std::cout << "PASSED" << std::endl; \
//             passed++; \
//         } else { \
//             std::cout << "FAILED" << std::endl; \
//             failed++; \
//         } \
//         total++; \
//     } while (false)

// int passed = 0;
// int failed = 0;
// int total = 0;

// // Helper function to clean up test files
// void cleanupTestFile(const std::string& filename) {
//     remove(filename.c_str());
// }

// // BASIC FUNCTIONALITY TESTS

// bool test_initialization() {
//     Tree emptyTree;
//     ASSERT(emptyTree.findNode("anything") == nullptr, "Empty tree should not find any nodes");
//     return true;
// }

// bool test_add_root_node() {
//     Tree testTree;
//     ASSERT(testTree.addFeatureOnSpine("", "Root", "Mouth"), "Should be able to add root node");
    
//     Node* root = testTree.findNode("Root");
//     ASSERT(root != nullptr, "Should find root node");
//     ASSERT(root->name == "Root", "Root node name should match");
//     ASSERT(root->type == "Mouth", "Root node type should match");
//     ASSERT(root->parent == nullptr, "Root node should have no parent");
//     ASSERT(root->leftTrib == nullptr, "Root should have no left tributary initially");
//     ASSERT(root->rightTrib == nullptr, "Root should have no right tributary initially");
//     ASSERT(root->next == nullptr, "Root should have no spine node initially");
    
//     return true;
// }

// bool test_add_feature_on_spine() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Columbia", "River");
//     ASSERT(tree.addFeatureOnSpine("Columbia", "Portland", "City"), "Should add to spine");
    
//     Node* columbia = tree.findNode("Columbia");
//     Node* portland = tree.findNode("Portland");
    
//     ASSERT(portland != nullptr, "Should find Portland node");
//     ASSERT(columbia->next == portland, "Columbia's next should point to Portland");
//     ASSERT(portland->parent == columbia->parent, "Portland's parent should be the same as Columbia's");
    
//     return true;
// }

// bool test_add_feature_on_branch() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Columbia", "River");
//     ASSERT(tree.addFeatureOnBranch("Columbia", "Willamette", "River", true), "Should add left branch");
    
//     Node* columbia = tree.findNode("Columbia");
//     Node* willamette = tree.findNode("Willamette");
    
//     ASSERT(willamette != nullptr, "Should find Willamette node");
//     ASSERT(willamette->parent == columbia, "Willamette's parent should be Columbia");
//     ASSERT(columbia->leftTrib == willamette, "Columbia's left tributary should be Willamette");
    
//     ASSERT(tree.addFeatureOnBranch("Columbia", "Snake", "Tributary", false), "Should add right branch");
//     Node* snake = tree.findNode("Snake");
//     ASSERT(snake != nullptr, "Should find Snake node");
//     ASSERT(columbia->rightTrib == snake, "Columbia's right tributary should be Snake");
//     ASSERT(snake->parent == columbia, "Snake's parent should be Columbia");
    
//     return true;
// }

// // EDGE CASE TESTS

// bool test_find_nonexistent_node() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Columbia", "River");
//     ASSERT(tree.findNode("NonExistent") == nullptr, "Should not find nonexistent node");
//     return true;
// }

// bool test_duplicate_additions() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Columbia", "River");
//     ASSERT(tree.addFeatureOnSpine("Columbia", "Portland", "City"), "First spine addition should work");
//     ASSERT(!tree.addFeatureOnSpine("Columbia", "Portland", "City"), "Duplicate spine addition should fail");
    
//     ASSERT(tree.addFeatureOnBranch("Columbia", "Willamette", "River", true), "First branch addition should work");
//     ASSERT(!tree.addFeatureOnBranch("Columbia", "Another", "River", true), "Duplicate left branch addition should fail");
    
//     return true;
// }

// bool test_save_and_load() {
//     const std::string testFile = "test_tree.bin";
    
//     // Build tree
//     Tree original;
//     original.addFeatureOnSpine("", "Columbia", "River");
//     original.addFeatureOnSpine("Columbia", "Portland", "City");
//     original.addFeatureOnBranch("Columbia", "Willamette", "River", true);
//     original.addFeatureOnBranch("Columbia", "Snake", "Tributary", false);
    
//     // Save and load
//     original.save(testFile);
//     Tree loaded;
//     loaded.load(testFile);
    
//     // Verify
//     Node* columbia = loaded.findNode("Columbia");
//     Node* portland = loaded.findNode("Portland");
//     Node* willamette = loaded.findNode("Willamette");
//     Node* snake = loaded.findNode("Snake");
    
//     ASSERT(columbia != nullptr, "Should load Columbia");
//     ASSERT(portland != nullptr, "Should load Portland");
//     ASSERT(willamette != nullptr, "Should load Willamette");
//     ASSERT(snake != nullptr, "Should load Snake");
    
//     // Verify structure integrity
//     ASSERT(columbia->next == portland, "Columbia's next should be Portland");
//     ASSERT(columbia->leftTrib == willamette, "Columbia's left trib should be Willamette");
//     ASSERT(columbia->rightTrib == snake, "Columbia's right trib should be Snake");
//     ASSERT(willamette->parent == columbia, "Willamette's parent should be Columbia");
//     ASSERT(snake->parent == columbia, "Snake's parent should be Columbia");
    
//     // Clean up
//     cleanupTestFile(testFile);
//     return true;
// }

// bool test_print_tree() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Columbia", "River");
//     tree.addFeatureOnSpine("Columbia", "Portland", "City");
    
//     // Just verify it doesn't crash - can't easily test output
//     std::cout << "\nPrinting tree (visual verification):" << std::endl;
//     tree.printTree();
//     return true;
// }

// // ADDITIONAL EDGE CASE TESTS

// bool test_add_to_nonexistent_parent() {
//     Tree tree;
//     ASSERT(!tree.addFeatureOnSpine("NonExistent", "ShouldFail", "Feature"), 
//            "Adding to non-existent parent should fail");
//     ASSERT(!tree.addFeatureOnBranch("NonExistent", "ShouldFail", "Feature", true), 
//            "Adding branch to non-existent parent should fail");
//     return true;
// }

// bool test_empty_node_name() {
//     Tree tree;
//     ASSERT(tree.addFeatureOnSpine("", "", "EmptyName"), 
//            "Should allow empty node name for root");
//     ASSERT(tree.findNode("") != nullptr, "Should find node with empty name");
    
//     ASSERT(tree.addFeatureOnSpine("", "NextNode", "Feature"),
//            "Should add spine to node with empty name");
    
//     return true;
// }

// bool test_empty_type() {
//     Tree tree;
//     ASSERT(tree.addFeatureOnSpine("", "EmptyType", ""), 
//            "Should allow empty type");
//     Node* node = tree.findNode("EmptyType");
//     ASSERT(node != nullptr, "Should find node with empty type");
//     ASSERT(node->type == "", "Node type should be empty");
    
//     return true;
// }

// bool test_deep_tree_structure() {
//     Tree tree;
    
//     // Create a deep spine structure
//     ASSERT(tree.addFeatureOnSpine("", "A", "Level1"), "Should add root node");
//     ASSERT(tree.addFeatureOnSpine("A", "B", "Level2"), "Should add B to spine");
//     ASSERT(tree.addFeatureOnSpine("B", "C", "Level3"), "Should add C to spine");
//     ASSERT(tree.addFeatureOnSpine("C", "D", "Level4"), "Should add D to spine");
//     ASSERT(tree.addFeatureOnSpine("D", "E", "Level5"), "Should add E to spine");
    
//     // Verify deep spine
//     Node* a = tree.findNode("A");
//     Node* b = tree.findNode("B");
//     Node* c = tree.findNode("C");
//     Node* d = tree.findNode("D");
//     Node* e = tree.findNode("E");
    
//     ASSERT(a != nullptr && b != nullptr && c != nullptr && d != nullptr && e != nullptr, 
//            "All nodes should exist");
    
//     ASSERT(a->next == b, "A's next should be B");
//     ASSERT(b->next == c, "B's next should be C");
//     ASSERT(c->next == d, "C's next should be D");
//     ASSERT(d->next == e, "D's next should be E");
    
//     // Add branches to various levels
//     ASSERT(tree.addFeatureOnBranch("A", "A-Left", "Branch", true), "Should add branch to A");
//     ASSERT(tree.addFeatureOnBranch("C", "C-Left", "Branch", true), "Should add branch to C");
//     ASSERT(tree.addFeatureOnBranch("C", "C-Right", "Branch", false), "Should add branch to C");
//     ASSERT(tree.addFeatureOnBranch("E", "E-Left", "Branch", true), "Should add branch to E");
    
//     // Verify branches
//     ASSERT(tree.findNode("A-Left") == a->leftTrib, "A's left branch should be A-Left");
//     ASSERT(tree.findNode("C-Left") == c->leftTrib, "C's left branch should be C-Left");
//     ASSERT(tree.findNode("C-Right") == c->rightTrib, "C's right branch should be C-Right");
//     ASSERT(tree.findNode("E-Left") == e->leftTrib, "E's left branch should be E-Left");
    
//     return true;
// }

// bool test_complex_tree_with_branches_on_branches() {
//     Tree tree;
    
//     // Create root and first branch
//     tree.addFeatureOnSpine("", "Root", "Base");
//     tree.addFeatureOnBranch("Root", "Branch1", "Branch", true);
    
//     // Add spine to branch
//     ASSERT(tree.addFeatureOnSpine("Branch1", "BranchSpine", "Feature"), 
//            "Should be able to add spine to branch node");
    
//     // Verify structure
//     Node* branch1 = tree.findNode("Branch1");
//     Node* branchSpine = tree.findNode("BranchSpine");
    
//     ASSERT(branch1 != nullptr && branchSpine != nullptr, "Nodes should exist");
//     ASSERT(branch1->next == branchSpine, "Branch1's next should be BranchSpine");
    
//     // Add branches to a spine node
//     tree.addFeatureOnSpine("Root", "Spine1", "Feature");
//     ASSERT(tree.addFeatureOnBranch("Spine1", "SpineBranch1", "Branch", true),
//            "Should add branch to spine node");
//     ASSERT(tree.addFeatureOnBranch("Spine1", "SpineBranch2", "Branch", false),
//            "Should add second branch to spine node");
    
//     // Verify structure
//     Node* spine1 = tree.findNode("Spine1");
//     Node* spineBranch1 = tree.findNode("SpineBranch1");
//     Node* spineBranch2 = tree.findNode("SpineBranch2");
    
//     ASSERT(spine1 != nullptr && spineBranch1 != nullptr && spineBranch2 != nullptr, 
//            "All nodes should exist");
//     ASSERT(spine1->leftTrib == spineBranch1, "Spine1's left branch should be SpineBranch1");
//     ASSERT(spine1->rightTrib == spineBranch2, "Spine1's right branch should be SpineBranch2");
    
//     return true;
// }

// bool test_load_invalid_file() {
//     Tree tree;
//     tree.addFeatureOnSpine("", "Root", "Base"); // Add something initially
    
//     // Attempt to load from non-existent file
//     const std::string nonExistentFile = "nonexistent_file.bin";
//     tree.load(nonExistentFile);
    
//     // Verify tree state - should still have root node
//     ASSERT(tree.findNode("Root") != nullptr, 
//            "Tree should maintain state after invalid load attempt");
    
//     return true;
// }

// bool test_modified_save_load() {
//     const std::string testFile = "test_tree_modified.bin";
    
//     // Create and save original tree
//     Tree original;
//     original.addFeatureOnSpine("", "Root", "Base");
//     original.addFeatureOnSpine("Root", "Node1", "Feature");
//     original.save(testFile);
    
//     // Load and modify
//     Tree modified;
//     modified.load(testFile);
//     modified.addFeatureOnSpine("Node1", "Node2", "Feature");
//     modified.addFeatureOnBranch("Root", "Branch", "Branch", true);
    
//     // Save and load again
//     modified.save(testFile);
//     Tree reloaded;
//     reloaded.load(testFile);
    
//     // Verify structure maintained through save-modify-save-load cycle
//     ASSERT(reloaded.findNode("Root") != nullptr, "Root should exist");
//     ASSERT(reloaded.findNode("Node1") != nullptr, "Node1 should exist");
//     ASSERT(reloaded.findNode("Node2") != nullptr, "Node2 should exist");
//     ASSERT(reloaded.findNode("Branch") != nullptr, "Branch should exist");
    
//     Node* root = reloaded.findNode("Root");
//     ASSERT(root->next == reloaded.findNode("Node1"), "Root's next should be Node1");
//     ASSERT(root->leftTrib == reloaded.findNode("Branch"), "Root's left branch should be Branch");
    
//     // Clean up
//     cleanupTestFile(testFile);
//     return true;
// }

// bool test_destroy_functionality() {
//     Tree* tree = new Tree();
//     tree->addFeatureOnSpine("", "Root", "Base");
//     tree->addFeatureOnSpine("Root", "Child1", "Feature");
//     tree->addFeatureOnBranch("Root", "Branch1", "Branch", true);
//     tree->addFeatureOnBranch("Root", "Branch2", "Branch", false);
    
//     // Destroying tree should not cause memory leaks or crashes
//     delete tree;
    
//     // If we get here without crashing, the test passed
//     return true;
// }

// bool test_columbia_river_example() {
//     // Test the actual example from main.cpp
//     Tree river;
//     ASSERT(river.addFeatureOnSpine("", "Lower Colombia", "Mouth"), "Should add root");
//     ASSERT(river.addFeatureOnBranch("Lower Colombia", "Colombia River", "River", true), "Should add left branch");
//     ASSERT(river.addFeatureOnBranch("Colombia River", "Snake Trit", "Tributary", false), "Should add right branch to branch");
//     ASSERT(river.addFeatureOnBranch("Lower Colombia", "Willamette River", "River", false), "Should add right branch");
    
//     // Add a chain of spine nodes
//     ASSERT(river.addFeatureOnSpine("Lower Colombia", "Astoria", "City"), "Should add spine node");
//     ASSERT(river.addFeatureOnSpine("Astoria", "St. Helens", "City"), "Should add spine node");
//     ASSERT(river.addFeatureOnSpine("St. Helens", "Portland", "City"), "Should add spine node");
    
//     // Verify some key relationships
//     Node* lowerColombia = river.findNode("Lower Colombia");
//     Node* colombiaRiver = river.findNode("Colombia River");
//     Node* willamette = river.findNode("Willamette River");
//     Node* astoria = river.findNode("Astoria");
//     Node* stHelens = river.findNode("St. Helens");
//     Node* portland = river.findNode("Portland");
    
//     ASSERT(lowerColombia->leftTrib == colombiaRiver, "Left branch should be Colombia River");
//     ASSERT(lowerColombia->rightTrib == willamette, "Right branch should be Willamette");
//     ASSERT(lowerColombia->next == astoria, "Next should be Astoria");
//     ASSERT(astoria->next == stHelens, "Astoria's next should be St. Helens");
//     ASSERT(stHelens->next == portland, "St. Helens' next should be Portland");
    
//     return true;
// }

// // Main test function
// int main() {
//     std::cout << "Running tree tests..." << std::endl;
    
//     // Basic functionality tests
//     RUN_TEST(test_initialization);
//     RUN_TEST(test_add_root_node);
//     RUN_TEST(test_add_feature_on_spine);
//     RUN_TEST(test_add_feature_on_branch);
//     RUN_TEST(test_find_nonexistent_node);
//     RUN_TEST(test_duplicate_additions);
//     RUN_TEST(test_save_and_load);
//     RUN_TEST(test_print_tree);
    
//     // Edge case tests
//     RUN_TEST(test_add_to_nonexistent_parent);
//     RUN_TEST(test_empty_node_name);
//     RUN_TEST(test_empty_type);
//     RUN_TEST(test_deep_tree_structure);
//     RUN_TEST(test_complex_tree_with_branches_on_branches);
//     RUN_TEST(test_load_invalid_file);
//     RUN_TEST(test_modified_save_load);
//     RUN_TEST(test_destroy_functionality);
//     RUN_TEST(test_columbia_river_example);
    
//     std::cout << "\nTest results: " << passed << " passed, " << failed << " failed, " << total << " total" << std::endl;
//     return failed == 0 ? 0 : 1;
// }