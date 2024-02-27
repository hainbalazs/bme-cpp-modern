// print()

/*
 A feladat egy olyat print() függvénycsaládot írni, amelyik meg tudja különböztetni, más formátumban írja ki a számokat, a karaktereket és a sztringeket.

A számokat (int, double, egyebek) önmagukban, pl. 5 vagy 5.1.
A karaktereket (pl. char vagy char16_t) aposztrófok között: 'a'.
A sztringeket (pl. char* vagy std::string) pedig idézőjelek között: "hello".
Egyéb típusokat ne lehessen kiírni vele.
A feladatot sablon metaprogramozással oldd meg!

 #Útmutatás.
 Elvileg csak három print() függvényre lesz szükséged, amelyek közül mindig valamelyiket az std::enable_if engedélyezi, a többit tiltja. Nézz szét a type_traits dokumentációjában, milyen sablonokat tudsz felhasználni és miket kell magadnak megírnod! Figyelned kell arra is, hogy T és T const eltérő típusok, ugyanakkor vissza lehet vezetni egyiket a másikra. Vigyázat, sok a buktató!
 */


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
struct isString{
    static constexpr bool value = false;
};

template <>
struct isString<std::string>{static constexpr bool value = true;};
template <>
struct isString<char*>{static constexpr bool value = true;};
template <>
struct isString<const char*>{static constexpr bool value = true;};


template <typename T>
void print(T what, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr, typename std::enable_if<!isChar<T>::value>::type * = nullptr){
    std::cout << what;
}
template <typename T>
void print(T what, typename std::enable_if<isChar<T>::value>::type * = nullptr){
    std::cout << "\'" << what << "\'" ;
}
template <typename T>
void print(	T what, typename
           std::enable_if<isString<T>::value>::type * = nullptr){
    std::cout << "\"" << what << "\"" << std::endl;
}

/*template <typename T>
void print(T what, typename
           std::enable_if<std::is_pointer<T>::value && isChar<decltype((*what))>::value>::type * = nullptr){
    std::cout << "\"" << what << "\"" << std::endl;
}*/




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
