#include <iostream>
#include <string>
int operator "" _binary (char const* n){
    int dec = 0;
    int pow = 1;
    size_t i = 0;
    while(n[i] != '\0') i++;
    i--;
    for(; i > 0; i--){
        dec += (n[i] - '0' + 1)*pow;
        pow *= 2;
    }
    return dec;
}

int main()
{
    std::cout << 1111_binary << std::endl;
    std::cout << 10000000_binary << std::endl;
    return 0;
}
