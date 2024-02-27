#include <iostream>
#include "mystring.h"

MyString&& createMyString(MyString && ref){
    return std::move(ref);
}

int main(){
    MyString a = "string", b;
    const MyString c = b = a;
    
    std::cout << a.getRefs() << std::endl;
    std::cout << ((c[3] == a[3])? "a[3] == b[3]" : "=/=" )<< std::endl;
    std::cout << a.getRefs() << ", " << b.getRefs() << std::endl;
    std::cout << a << std::endl;
    
    b = "egosztott";
    b = 'm' + b;
    b = b + " ";
    
    std::cout << "ez egy " + b  + (a += '!') << std::endl;
    std::cout << "merete: " << b.length() <<std::endl;
    std::cout << "c referenciai: " << c.getRefs() << std::endl << "olvass be egy szoveget: ";
    MyString beolvas;
    std::cin >> beolvas; // semmit nem tud még beolvasni
    std::cout << "beolvasott szoveg: " << beolvas << std::endl;
    
    MyString rValCheck = createMyString(MyString("r-value"));
    std::cout << rValCheck << std::endl;
    
    try {
        MyString f, g;
        std::cout << f + g;
    }
    catch(std::exception& e){
        std::cout << "exception: " << e.what();
    }
    
    
    return 0;
}

