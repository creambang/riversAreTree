#include "riverTree.hpp"

int main() {
    DoublyLinkedList mainRiver;
    std::cout << "\nColumbia River Tree Structure: " << std::endl;
    mainRiver.addNode("Astoria", "City", false, "", "Youngs", "Grays");
    mainRiver.addNode("Rufus", "City", false);
    // mainRiver.addNode("Wanapum", "Dam");
    // mainRiver.addNode("Portland", "City");
    // mainRiver.addNode("Cascade Locks", "City");
    // mainRiver.addNode("Bonneville Dam", "Dam");
    // mainRiver.addNode("The Dalles", "City");
    // mainRiver.addNode("Rufus", "City");
    // mainRiver.addNode("John Day", "Dam");
    // mainRiver.addNode("Umatilla", "City");
    // mainRiver.addNode("McNary", "Dam");
    // mainRiver.addNode("Mattawa", "City");
    // mainRiver.addNode("Priest Rapids", "Dam");
    // mainRiver.addNode("Vantage", "City");
    // mainRiver.addNode("Wanapum", "Dam");
    // mainRiver.addNode("Wenatchee", "City");
    // mainRiver.addNode("Rock Island", "Dam");
    // mainRiver.addNode("Chelan County", "City");
    // mainRiver.addNode("Rocky Reach", "Dam");
    // mainRiver.addNode("Pateros", "City");
    // mainRiver.addNode("Wells", "Dam");
    // mainRiver.addNode("Bridgeport", "City");
    // mainRiver.addNode("Chief Joseph", "Dam");
    // mainRiver.addNode("Coulee City", "City");
    // mainRiver.addNode("Grand Coulee", "Dam");
    // mainRiver.addNode("Little Falls", "Dam");
    // mainRiver.addNode("Long Lake", "Dam");
    // mainRiver.addNode("Nine Mile Falls", "City");
    // mainRiver.addNode("Monroe", "Dam");

    mainRiver.display();
    mainRiver.searchRoute("Astoria", "Portland"); // Example search for a node
}
