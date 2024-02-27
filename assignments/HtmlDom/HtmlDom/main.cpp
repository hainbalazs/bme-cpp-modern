#include <iostream>
#include "Node.hpp"
#include "Document.hpp"


int main(int argc, const char * argv[]) {
    Document DOM;
        
    DOM.treeRoot->addChild(Paragraph("firstP"));
    auto ListToAdd = DOM.treeRoot->addChild(UnorderedList("list"));
    ListToAdd->addChild(ListItem("item1"));
    ListToAdd->addChild(ListItem());
    DOM.treeRoot->addChild(Paragraph("secondP"));
        
    DOM.treeRoot->print();
    std::cout << std::endl;
    
    auto toDel = DOM.getElementById("firstP");
    toDel->getParent()->removeChild(*toDel);
    
    auto toPrint = DOM.getElementById("list")->nextSibling();
    toPrint->print();
    std::cout << std::endl;
    
    
    return 0;
}
