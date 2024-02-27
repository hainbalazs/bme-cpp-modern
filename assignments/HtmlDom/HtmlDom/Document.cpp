#include "Document.hpp"
#include "Node.hpp"

Document::Document() {
    /* muszáj shared legyen hogy lehessen rá weak_ptr -t állítani */
    treeRoot = std::make_shared<Body>(Body());
    Node::setMap(&elements);
}

std::shared_ptr<Node> Document::getElementById(std::string id) {
    return elements[id];
}
