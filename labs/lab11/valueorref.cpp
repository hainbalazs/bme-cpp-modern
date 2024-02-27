#include <iostream>
#include <type_traits>

template <typename T>
using type = std::conditional<std::is_class<T>::value, const T&, T>;

template <typename T>
type<T> greater(type<T> a, type<T> b){
    return a > b ? a : b; 
}