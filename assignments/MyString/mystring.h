#include <iostream>

class MyString {
public:
    MyString();
    MyString(const char *);
    MyString(MyString const &);
    MyString(MyString &&) noexcept;
    
    MyString & operator=(MyString const &);
    MyString & operator=(MyString &&) noexcept;
    
    // index
    const char operator[](size_t) const;
    char& operator[](size_t);
    const char at(size_t) const;
    char& at(size_t);
    // str + str
    MyString operator+ (MyString const &) const;
    MyString& operator+=(MyString const &);
    
    // str + char
    MyString operator+ (const char);
    MyString& operator+=(const char);
    
    // @return length of the string
    size_t length() const;
    
    // @returns string in C format
    const char * c_str() const;
    operator const char*() const {return c_str();}
    
    friend std::istream & operator>>(std::istream& os, MyString & s);
    
    // hany referencia mutat az adott stringre -- csak teszteles miatt
    size_t getRefs() const {return str->getRefs();}
    
    ~MyString();
    
private:
    class StringValue {
        /* maga a sztring osztály megvalósítása
         * null terminált karaktertömb
         * szokásos ctor, copy ctor, move ctor, =, move =, dtor,
         * +, += (sztring + sztring), (sztring + char), <<, >>, [], .length()
         *
         * + referencia számláló (size_t)
         * */
    public:
        StringValue();
        StringValue(const char *);
        StringValue(StringValue const &);
        StringValue(StringValue &&);
        
        StringValue & operator=(StringValue const &);
        StringValue & operator=(StringValue &&);
        // index
        
        // str + str
        StringValue operator+ (StringValue const &) const;
        StringValue operator+ (char const &) const;
        
        ~StringValue();
        
        //itt se biztos hogy mindketto kell
        const char operator[](size_t) const;
        char& operator[](size_t);
        
        
        // @return length of the string
        size_t length() {return length_;}
        
        // c_str
        const char * c_str(){return (string_) ? string_: "" ; }
        void readFromStream(std::istream &);
        
        // references
        void incrRef() { references_++; }
        void decrRef() { references_--; }
        size_t getRefs() const { return references_; }
        
    private:
        char *string_;
        size_t length_;
        size_t references_;
    };
    
    StringValue * str;
    void killOneRef();
};

// char + str
MyString operator+ (const char, MyString const &);
MyString operator+ (const char *, MyString const &);


std::istream & operator>>(std::istream& os, MyString & s);
std::ostream & operator<<(std::ostream& os, MyString const & s);
