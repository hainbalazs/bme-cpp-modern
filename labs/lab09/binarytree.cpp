#include <iostream>
#include <algorithm>

template <typename T>
class Node {
  private:
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
  public:
    Node(): data{}, left{nullptr}, right{nullptr}{}
    
    Node(Node const& original) : data(original.data) {
        Node *newLeft = nullptr;
        Node *newRight = nullptr;

        try{
            if(original.left == nullptr)
                newLeft = nullptr;
            else
                newLeft = new Node(*original.left);

            if(original.right == nullptr)
                newRight = nullptr;
            else 
                newRight = new Node(*original.right);
        }
        
        catch(...){
            delete newLeft;
            delete newRight;
            throw;
        }
        
        left = newLeft;
        right = newRight;
        
    }

    Node(Node && original) noexcept : data(std::move(original.data))  {
        left = original.left;
        original.left = nullptr;
        right = original.right;
        original.right = nullptr;
    }

    Node& operator=(Node const other){
        std::swap(this->data, other.data);
        std::swap(this->left, other.left);
        std::swap(this->right, other.right);
    }

    void deleteRecursively(Node *n) noexcept{
        if(n != nullptr){
            deleteRecursively(n->left);
            deleteRecursively(n->right);
            delete n;
        }
    }
    ~Node() noexcept {
        deleteRecursively(left);
        deleteRecursively(right);
    }

};



int main(){

    return 0;
}