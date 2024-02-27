#include <iostream>
#include <string>


std::string operator "" _s (const char* s, size_t len){
    return std::string(s, len);
}

int main()
{
    std::cout << "hello"_s + "vilag" << std::endl;
    std::cout << "hello\0vilag"_s.length() << std::endl;
    return 0;
}
