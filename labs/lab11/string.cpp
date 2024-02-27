#include <iostream>
#include <cctype>

template <typename TRAITCLASS = CharTraits>
class String {
  private:
    TRAITCLASS::Type data[100];
 
  public:
    String() {
        data[0] = 0;
    }
 
    String(char const *init) {
        strcpy(data, init);
    }
    
    bool operator==(String const &rhs) {
        String const &lhs = *this;
        size_t i;
        for (i = 0; lhs.data[i] != 0 && rhs.data[i] != 0;  ++i)
            if (!TRAITCLASS::equal(lhs.data[i], rhs.data[i]))
                return false;
        return lhs.data[i] == 0 && rhs.data[i] == 0;
    }
};
 
 template <typename T>
struct CharTraits {
};


template <>
struct CharTraits<char> {
    using Type = char;
    static bool equal(char c1, char c2) { return std::tolower(c1) == std::tolower(c2);} 
};

template<>
struct CharTraits<char16_t> {
    using Type = char16_t;
    static bool equal(char c1, char c2) { return std::tolower(c1) == std::tolower(c2);} 
};

template<>
struct CharTraits<char32_t> {
    using Type = char32_t;
    static bool equal(char c1, char c2) { return std::tolower(c1) == std::tolower(c2);} 
};
 
int main() {
    String s1 = "hello", s2 = "HeLLo";
    std::cout << (s1 == s2);
}
