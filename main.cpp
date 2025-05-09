#include "tree.hpp"

int main() {
    Tree river;
    river.addFeatureOnSpine("", "Lower Colombia", "Mouth");
    river.addFeatureOnBranch("Lower Colombia", "Colombia River", "River", true);
    river.addFeatureOnBranch("Colombia River", "Snake Trit", "Tributary", false);
    river.addFeatureOnBranch("Lower Colombia", "Willamette River", "River", false);
    river.addFeatureOnSpine("Lower Colombia", "Astoria", "City");
    river.addFeatureOnSpine("Astoria", "St. Helens", "City");
    river.addFeatureOnSpine("St. Helens", "Portland", "City");
    river.addFeatureOnSpine("Portland", "Bonneville Dam",  "Dam");
    river.addFeatureOnSpine("Bonneville Dam", "The Dalles", "Dam");
    river.addFeatureOnSpine("The Dalles", "John Day", "Dam");
    river.addFeatureOnSpine("John Day", "McNary", "Dam");
    river.addFeatureOnSpine("McNary", "Priest Rapids", "Dam");
    river.addFeatureOnSpine("Priest Rapids", "Wanapum", "Dam");
    river.addFeatureOnSpine("Wanapum", "Rock Island", "Dam");
    river.addFeatureOnSpine("Rock Island", "Rocky Reach", "Dam");
    river.addFeatureOnSpine("Rocky Reach", "Wells", "Dam");
    river.addFeatureOnSpine("Wells", "Chief Joseph", "Dam");
    river.addFeatureOnSpine("Chief Joseph", "Grand Coulee", "Dam");
    river.addFeatureOnSpine("Grand Coulee", "Little Falls", "Dam");
    river.addFeatureOnSpine("Little Falls", "Long Lake", "Dam");
    river.addFeatureOnSpine("Long Lake", "Nine Mile", "Dam");
    river.addFeatureOnSpine("Nine Mile", "Monroe", "Tail");

    river.printTree();
    river.traverseTree();

    return 0;
}
