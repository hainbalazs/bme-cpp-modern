#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Node : public std::enable_shared_from_this<Node>{
protected:
    /* ~ absztrakt osztály */
    Node(std::string id, std::string tag): id_{std::move(id)}, tag_{std::move(tag)} {  }
    
    std::string id_;
    std::string tag_;
    
    std::weak_ptr<Node> parentNode;
    std::weak_ptr<Node> thisNode;
    std::vector<std::shared_ptr<Node>> children;
    
    /* lehetne referencia is, de így legalább tudom ellenőrizni, hogy be lett állíta */
    static std::map<std::string, std::shared_ptr<Node>>* elementHolder;
    
public:
    static void setMap(std::map<std::string, std::shared_ptr<Node>>* map){
        elementHolder = map;
    }
    
    virtual void print() const;
    std::shared_ptr<Node> getParent() const;
    std::shared_ptr<Node> addChild(Node const & child);
    void removeChild(Node & child);
    std::shared_ptr<Node> getFirstChild() const;
    std::shared_ptr<Node> prevSibling() const;
    std::shared_ptr<Node> nextSibling() const;
    
    Node(Node const & Lref);
    Node(Node && Rref);
    Node & operator=(Node n);
    
    virtual ~Node() = default;
};


class Body : public Node {
public:
    Body(std::string id = "") : Node{std::move(id), "body"} {};
};
class UnorderedList : public Node {
public:
    UnorderedList(std::string id = "") : Node{std::move(id), "ul"} {};
};
class Paragraph : public Node {
public:
    Paragraph(std::string id = "") : Node{std::move(id), "p"} {};
};
class ListItem : public Node {
public:
    ListItem(std::string id = "") : Node{std::move(id), "li"} {};
};


#endif /* Node_hpp */
