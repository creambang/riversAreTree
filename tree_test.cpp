#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // for remove()

// Simple test framework
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << message << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            return false; \
        } \
    } while (false)

#define RUN_TEST(test) \
    do { \
        std::cout << "Running " << #test << "... "; \
        if (test()) { \
            std::cout << "PASSED" << std::endl; \
            passed++; \
        } else { \
            std::cout << "FAILED" << std::endl; \
            failed++; \
        } \
        total++; \
    } while (false)

int passed = 0;
int failed = 0;
int total = 0;

// Test cases
bool test_initialization() {
    Tree emptyTree;
    ASSERT(emptyTree.findNode("anything") == nullptr, "Empty tree should not find any nodes");
    return true;
}

bool test_add_root_node() {
    Tree testTree;
    ASSERT(testTree.addFeatureOnSpine("", "Root", "Mouth"), "Should be able to add root node");
    
    Node* root = testTree.findNode("Root");
    ASSERT(root != nullptr, "Should find root node");
    ASSERT(root->name == "Root", "Root node name should match");
    ASSERT(root->type == "Mouth", "Root node type should match");
    ASSERT(root->parent == nullptr, "Root node should have no parent");
    
    return true;
}

bool test_add_feature_on_spine() {
    Tree tree;
    tree.addFeatureOnSpine("", "Columbia", "River");
    ASSERT(tree.addFeatureOnSpine("Columbia", "Portland", "City"), "Should add to spine");
    
    Node* portland = tree.findNode("Portland");
    ASSERT(portland != nullptr, "Should find Portland node");
    ASSERT(portland->parent == tree.findNode("Columbia"), "Portland's parent should be Columbia");
    
    return true;
}

bool test_add_feature_on_branch() {
    Tree tree;
    tree.addFeatureOnSpine("", "Columbia", "River");
    ASSERT(tree.addFeatureOnBranch("Columbia", "Willamette", "River", true), "Should add left branch");
    
    Node* willamette = tree.findNode("Willamette");
    ASSERT(willamette != nullptr, "Should find Willamette node");
    ASSERT(willamette->parent == tree.findNode("Columbia"), "Willamette's parent should be Columbia");
    ASSERT(tree.findNode("Columbia")->leftTrib == willamette, "Columbia's left tributary should be Willamette");
    
    ASSERT(tree.addFeatureOnBranch("Columbia", "Snake", "Tributary", false), "Should add right branch");
    Node* snake = tree.findNode("Snake");
    ASSERT(snake != nullptr, "Should find Snake node");
    ASSERT(tree.findNode("Columbia")->rightTrib == snake, "Columbia's right tributary should be Snake");
    
    return true;
}

bool test_find_nonexistent_node() {
    Tree tree;
    tree.addFeatureOnSpine("", "Columbia", "River");
    ASSERT(tree.findNode("NonExistent") == nullptr, "Should not find nonexistent node");
    return true;
}

bool test_duplicate_additions() {
    Tree tree;
    tree.addFeatureOnSpine("", "Columbia", "River");
    ASSERT(tree.addFeatureOnSpine("Columbia", "Portland", "City"), "First spine addition should work");
    ASSERT(!tree.addFeatureOnSpine("Columbia", "Portland", "City"), "Duplicate spine addition should fail");
    
    ASSERT(tree.addFeatureOnBranch("Columbia", "Willamette", "River", true), "First branch addition should work");
    ASSERT(!tree.addFeatureOnBranch("Columbia", "Another", "River", true), "Duplicate left branch addition should fail");
    
    return true;
}

bool test_save_and_load() {
    const std::string testFile = "test_tree.bin";
    
    // Build tree
    Tree original;
    original.addFeatureOnSpine("", "Columbia", "River");
    original.addFeatureOnSpine("Columbia", "Portland", "City");
    original.addFeatureOnBranch("Columbia", "Willamette", "River", true);
    original.addFeatureOnBranch("Columbia", "Snake", "Tributary", false);
    
    // Save and load
    original.save(testFile);
    Tree loaded;
    loaded.load(testFile);
    
    // Verify
    ASSERT(loaded.findNode("Columbia") != nullptr, "Should load Columbia");
    ASSERT(loaded.findNode("Portland") != nullptr, "Should load Portland");
    ASSERT(loaded.findNode("Willamette") != nullptr, "Should load Willamette");
    ASSERT(loaded.findNode("Snake") != nullptr, "Should load Snake");
    
    // Clean up
    remove(testFile.c_str());
    return true;
}

bool test_print_tree() {
    Tree tree;
    tree.addFeatureOnSpine("", "Columbia", "River");
    tree.addFeatureOnSpine("Columbia", "Portland", "City");
    
    // Just verify it doesn't crash - can't easily test output
    std::cout << "\nPrinting tree (visual verification):" << std::endl;
    tree.printTree();
    return true;
}

int main() {
    std::cout << "Running tree tests..." << std::endl;
    
    RUN_TEST(test_initialization);
    RUN_TEST(test_add_root_node);
    RUN_TEST(test_add_feature_on_spine);
    RUN_TEST(test_add_feature_on_branch);
    RUN_TEST(test_find_nonexistent_node);
    RUN_TEST(test_duplicate_additions);
    RUN_TEST(test_save_and_load);
    RUN_TEST(test_print_tree);
    
    std::cout << "\nTest results: " << passed << " passed, " << failed << " failed, " << total << " total" << std::endl;
    return failed == 0 ? 0 : 1;
}