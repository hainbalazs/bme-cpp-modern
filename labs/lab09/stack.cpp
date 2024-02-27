#include <iostream>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <string>

template <typename T>
class Stack {
  public:
    explicit Stack(size_t max_size);
    Stack(Stack const &orig);
    Stack & operator=(Stack const &orig) = delete;
    ~Stack() noexcept;
    void push(T const &what);
    T pop();
    bool empty() const noexcept;
  private:
    size_t size_;
    size_t max_size_;
    T *pData_;
};


template <typename T>
Stack<T>::Stack(size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    pData_ = static_cast<T*>(::operator new(sizeof(T) * max_size_));
}


template <typename T>
Stack<T>::Stack(Stack<T> const &orig): Stack(orig.max_size_) {
    size_ = orig.size_;
    for (size_t i = 0; i != size_; ++i)
        new (&pData_[i]) T{orig.pData_[i]};
}


template <typename T>
Stack<T>::~Stack() noexcept { // nem dobhat
    for (size_t i = 0; i != size_; ++i)
        pData_[i].~T();
    ::operator delete(pData_);
}


/* Push element onto stack. */
template <typename T>
void Stack<T>::push(T const &what) {
    if(size_ == max_size_)
        throw std::out_of_range("Tele van a stack");
    new (&pData_[size_]) T{what};
    size_++;
}


/* Pop element from top of the stack. */
template <typename T>
T Stack<T>::pop() {
    if(empty())
        throw std::out_of_range("Üres a stack");

    T saved{pData_[size_-1]};
    pData_[size_-1].~T();
    size_--;
    return saved;
}


template <typename T>
bool Stack<T>::empty() const noexcept {
    return size_ == 0;
}


int main() {
    try{Stack<std::string> s(100);
    std::string word;
    while (std::cin >> word)
        s.push(word);
    while (!s.empty())
        std::cout << s.pop() << std::endl;
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
}
