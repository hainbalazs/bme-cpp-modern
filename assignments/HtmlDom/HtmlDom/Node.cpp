#include "Node.hpp"
#include <iostream>
#include <utility>

std::map<std::string, std::shared_ptr<Node>>* Node::elementHolder = nullptr;

void Node::print() const {
    std::cout << "<" << tag_ << (id_ != "" ? (" id=\"" + id_ + "\"") : "") << ">";
    for(auto e: children)
        if(e)
            e->print();
    std::cout << "</" << tag_ << ">";
}

std::shared_ptr<Node> Node::getParent() const{
    return parentNode.lock();
}

std::shared_ptr<Node> Node::addChild(Node const & child){
    auto childPtr = std::make_shared<Node>(child);
    childPtr->parentNode = shared_from_this();
    children.push_back(childPtr);
    
    if(elementHolder && child.id_ != "")
        elementHolder->insert(std::pair<std::string, std::shared_ptr<Node>>(child.id_, childPtr));
    
    return childPtr;
}
void Node::removeChild(Node & child){
    for (auto it = children.begin(); it != children.end(); it++)
        if(!*it && &(**it) == &child)
            children.erase(it);
    
    if(elementHolder && child.id_ != "")
        elementHolder->erase(child.id_);
}
std::shared_ptr<Node> Node::getFirstChild() const {
    return (children.size() == 0 ? nullptr: children.front());
}
std::shared_ptr<Node> Node::prevSibling() const {
    auto s_ptr = parentNode.lock();
    if(s_ptr)
        for (auto it = s_ptr->children.begin(); it < s_ptr->children.end(); it++)
            if(&(**it) == this)
                return (it-1 < s_ptr->children.begin() ? nullptr : *(it-1));
            
    return nullptr;
}
std::shared_ptr<Node> Node::nextSibling() const {
    auto s_ptr = parentNode.lock();
    if(s_ptr)
        for (auto it = s_ptr->children.begin(); it < s_ptr->children.end(); it++)
            if(&(**it) == this)
                return (it+1 > s_ptr->children.end() ? nullptr : *(it+1));
    
    return nullptr;
}

Node::Node(const Node &Lref): Node::Node{Lref.id_, Lref.tag_} {
    parentNode = Lref.parentNode;
    
    for(auto c: Lref.children)
        children.push_back(std::make_shared<Node>(*c));
}

Node::Node(Node &&Rref){
    id_ = std::move(Rref.id_);
    tag_ = std::move(Rref.tag_);
    parentNode = std::move(Rref.parentNode);
    children = std::move(Rref.children);
}


Node &Node::operator=(Node n) { 
    Node copy = n;
    std::swap(id_, copy.id_);
    std::swap(tag_, copy.tag_);
    std::swap(parentNode, copy.parentNode);
    std::swap(children, copy.children);

    return *this;
}

