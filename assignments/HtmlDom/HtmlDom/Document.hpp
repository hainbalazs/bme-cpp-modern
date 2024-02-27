#ifndef Document_hpp
#define Document_hpp

#include <iostream>
#include <map>
#include "Node.hpp"

class Document{
    std::map<std::string, std::shared_ptr<Node>> elements;
    
public:
    Document();
    std::shared_ptr<Body> treeRoot;
    std::shared_ptr<Node> getElementById(std::string id);
    std::shared_ptr<Node> prevSibling();
    std::shared_ptr<Node> nextSibling();
    
    void print();
    
    ~Document() = default;
};


#endif /* Document_hpp */
