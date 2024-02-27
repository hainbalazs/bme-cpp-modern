//#define MOVE

#include <iostream>
#include <cstring>
#include "mystring.h"


MyString::MyString(): str{nullptr} {}
MyString::MyString(const char * s) {
    if(s != nullptr)
        str = new StringValue(s);
    else
        str = nullptr;
}
MyString::MyString(MyString const & other): str{other.str}{
#ifdef MOVE
    std::cout << "sima cctor" << std::endl;
#endif // MOVE
    if(str != nullptr)
    str->incrRef();
    }
    MyString::MyString(MyString && other) noexcept : str{other.str}{
#ifdef MOVE
        std::cout << "move ctor" << std::endl;
#endif // MOVE
        other.str = nullptr;
    }
    MyString & MyString::operator=(MyString const & other){
#ifdef MOVE
        std::cout << "sima op=" <<std::endl;
#endif // MOVE
        if(this != &other){
            killOneRef();
            str = other.str;
            str->incrRef();
        }
        return *this;
    }
    
    MyString & MyString::operator=(MyString && other) noexcept{
#ifdef MOVE
        std::cout << "move op=" << std::endl;
#endif // MOVE
        if(this != &other){
            killOneRef();
            str = other.str;
            other.str = nullptr;
        }
        return *this;
    }
    // index
    const char MyString::operator[](size_t index) const{
        return (*str)[index];
    }
    
    char & MyString::operator[](size_t index){
        if(getRefs() > 1){
            StringValue *newStr = new StringValue(*str);
            killOneRef();
            str = newStr;
        }
        return (*str)[index];
    }
    
    const char MyString::at(size_t index) const {
        if(index >= length())
            throw std::out_of_range("Tulindexeles!");
        if(str == nullptr)
            throw std::logic_error("Inicializalatlan sztringet indexelsz");
        return (*this)[index];
    }
    
    char & MyString::at(size_t index){
        if(index >= length())
            throw std::out_of_range("Tulindexeles!");
        if(str == nullptr)
            throw std::logic_error("Inicializalatlan sztringet indexelsz");
        return (*this)[index];
    }
    
    
    // @return length of the string
    size_t MyString::length() const {
        return str->length();
    }
    
    // str + str
    MyString MyString::operator+ (MyString const & other) const {
        if(this->str == nullptr)
            if(other.str == nullptr)
                return MyString("");
            else
                return other;
        if(other.str == nullptr)
            return *this;
            
        MyString result;
        result.str = new StringValue(*str + *(other.str));
        return result;
    }
    MyString operator+(const char* s1, MyString const & s2){
        return MyString(s1) + s2;
    }
    
    MyString& MyString::operator+=(MyString const & other){
        return (*this = *this + other);
    }
    
    // str + char
    MyString MyString::operator+ (const char c){
        const char cMask[2] = {c, '\0'};
        return *this + MyString(cMask);
    }
    
    MyString operator+ (const char c, MyString const & s){
        const char cMask[2] = {c, '\0'};
        return MyString(cMask) + s;
    }
    
    MyString& MyString::operator+=(const char c){
        return (*this = *this + c);
    }
    
    const char * MyString::c_str() const {
        return str->c_str();
    }
    
    std::ostream & operator<<(std::ostream& os, MyString const &s){
        os << s.c_str();
        return os;
    }
    std::istream & operator>>(std::istream& is, MyString &s){
        MyString newS;
        newS.str = new MyString::StringValue;
        newS.str->readFromStream(is);
        s = newS;
        return is;
    }
    
    void MyString::killOneRef(){
        if(str == nullptr)
            return;
        str->decrRef();
        if(str->getRefs() == 0)
            delete str;
    }
    
    MyString::~MyString(){
        killOneRef();
    }
    MyString::StringValue::StringValue(): string_{nullptr}, length_{0}, references_{1} {}
    MyString::StringValue::StringValue(const char * s) :string_{new char[strlen(s) + 1]}, length_{strlen(s)}, references_{1}{
        strcpy(string_, s);
    }
    MyString::StringValue::StringValue(StringValue const & other): string_{new char[other.length_ + 1]}, length_{other.length_}, references_{1}{
        strcpy(string_, other.string_);
    }
    MyString::StringValue::StringValue(StringValue && other):string_{other.string_}, length_{other.length_}, references_{1}{
        other.string_ = nullptr;
    }
    
    MyString::StringValue & MyString::StringValue::operator=(StringValue const & other){
        if(this != &other){
            delete[] string_;
            string_ = new char[other.length_ + 1];
            length_ = other.length_;
            references_ = 1;
            strcpy(string_, other.string_);
        }
        return *this;
    }
    
    MyString::StringValue & MyString::StringValue::operator=(StringValue && other){
        if(this != &other){
            delete[] string_;
            string_ = other.string_;
            length_ = other.length_;
            references_ = 1;
            other.string_ = nullptr;
        }
        return *this;
    }
    // index - nem kell konstans
    char& MyString::StringValue::operator[](size_t idx){
        return string_[idx];
    }
    
    // str + str
    MyString::StringValue MyString::StringValue::operator+ (StringValue const & other) const {
        StringValue result;
        result.string_ = new char[length_ + other.length_ + 1];
        result.length_ = length_ + other.length_;
        result.references_ = 1;
        strcpy(result.string_, string_);
        strncat(result.string_, other.string_, other.length_ + 1);
        return result;
    }
    MyString::StringValue MyString::StringValue::operator+ (char const & c) const {
        StringValue result;
        result.string_ = new char[length_ + 2];
        result.length_ = length_ + 1;
        strcpy(result.string_, string_);
        result.string_[length_] = c;
        result.string_[length_+1] = '\0';
        return result;
    }
    
    /* nem kell fűzhető legyen */
    void MyString::StringValue::readFromStream(std::istream & is){
        char c;
        StringValue uj = "";
        
        while(is.get(c) && !isspace(c))
            uj = uj + c;
        
        *this = uj;
    }
    
    MyString::StringValue::~StringValue(){
        delete[] string_;
    }
    
    
