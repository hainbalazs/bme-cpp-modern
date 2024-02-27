#include <iostream>
#include <type_traits>
#include <string>

template <typename T>
struct isChar{
    static constexpr bool value = false;
};

template <>
struct isChar<char>{ static constexpr bool value = true;};
template <>
struct isChar<char32_t>{ static constexpr bool value = true;};
template <>
struct isChar<char16_t>{ static constexpr bool value = true;};
template <typename T>
struct isChar<const T>{ static constexpr bool value = isChar<T>::value;};

template <typename T>
struct isString{
    static constexpr bool value = false;
};

template <>
struct isString<std::string>{static constexpr bool value = true;};
template <typename T>
struct isString<T*>{static constexpr bool value = isChar<T>::value;};


template <typename T>
void print(T what, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr, typename std::enable_if<!isChar<T>::value>::type * = nullptr){
    std::cout << what;
}
template <typename T>
void print(T what, typename std::enable_if<isChar<T>::value>::type * = nullptr){
    std::cout << "\'" << what << "\'" ;
}
template <typename T>
void print(T what, typename std::enable_if<isString<T>::value>::type * = nullptr){
    std::cout << "\"" << what << "\"" << std::endl;
}

/*
ha ez műkdöne, nem lenne szükség a 16-17, 26-27. sorra, de nem világos miért nem működik.
a fordító azt a hibát dobja, hogy típust várt, de std::remove_pointer<T>::type -ot kapott

template <typename T>
void print(T what, 
typename std::enable_if<isString<T>::value || (
    std::is_pointer<T>::value && isChar<std::remove_const<std::remove_pointer<T>::type>::type>::value)>::type * = nullptr){
    std::cout << "\"" << what << "\"" << std::endl;
}
*/


int main(int argc, const char * argv[]) {
    print(2);
    int const a = 0;
    print(a);
    print(3.1);
    print('a');
    const char as[3] = "ab";
    char bs[3] =  "bc";
    std::string cs= "cd";
    print(as);
    print(bs);
    print(cs);
    print("c++");
    
    return 0;
}