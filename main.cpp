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
    river.addFeatureOnBranch("Lower Colombia", "Columbia River", "River", true);
    river.addFeatureOnBranch("Columbia River", "Snake Trit", "Tributary", false);
    river.addFeatureOnBranch("Lower Colombia", "Willamette River", "River", false);
    
    // Add a chain of spine nodes
    river.addFeatureOnSpine("Lower Colombia", "Astoria", "City");
    river.addFeatureOnSpine("Astoria", "St. Helens", "City");
    river.addFeatureOnSpine("St. Helens", "Portland", "City");
    
    // Print the tree structure
    river.printTree();
    river.traverseTree();
    
    return 0;
}