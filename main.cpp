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
    river.addFeatureOnSpine("Portland", "Cascade Locks", "City");
    river.addFeatureOnSpine("Cascade Locks", "Bonneville", "Dam");
    river.addFeatureOnSpine("Bonneville", "The Dalles", "City");
    river.addFeatureOnSpine("The Dalles", "Rufus", "City");
    river.addFeatureOnSpine("Rufus", "John Day", "Dam");
    river.addFeatureOnSpine("John Day", "Umatilla", "City");
    river.addFeatureOnSpine("Umatilla", "McNary", "Dam");
    river.addFeatureOnSpine("McNary", "Mattawa", "City");
    river.addFeatureOnSpine("Mattawa", "Priest Rapids", "Dam");
    river.addFeatureOnSpine("Priest Rapids", "Vantage", "City");
    river.addFeatureOnSpine("Vantage", "Wanapum", "Dam");
    river.addFeatureOnSpine("Wanapum", "Wenatchee", "City");
    river.addFeatureOnSpine("Wenatchee", "Rock Island", "Dam");
    river.addFeatureOnSpine("Rock Island", "Chelan County", "City");
    river.addFeatureOnSpine("Chelan County", "Rocky Reach", "Dam");
    river.addFeatureOnSpine("Rocky Reach", "Pateros", "City");
    river.addFeatureOnSpine("Pateros", "Wells", "Dam");
    river.addFeatureOnSpine("Wells", "Bridgeport", "City");
    river.addFeatureOnSpine("Bridgeport", "Chief Joseph", "Dam");
    river.addFeatureOnSpine("Chief Joseph", "Coulee City", "City");
    river.addFeatureOnSpine("Coulee City", "Grand Coulee", "Dam");
    river.addFeatureOnSpine("Grand Coulee", "Little Falls", "Dam");
    river.addFeatureOnSpine("Little Falls", "Long Lake", "Dam");
    river.addFeatureOnSpine("Long Lake", "Nine Mile Falls", "City");
    river.addFeatureOnSpine("Nine Mile Falls", "Monroe", "Dam");

    Node* temp = river.findNode("Snake Trit")->parent;
    std::cout << temp->name << std::endl;
    
    // Print the tree structure
    river.printTree();
    
    return 0;
}