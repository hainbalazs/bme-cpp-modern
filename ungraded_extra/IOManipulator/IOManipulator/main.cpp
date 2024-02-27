#include <iostream>
#include <string>

/* A) feladat: */
class BinPrinter {
    std::ostream & os;
    
public:
    enum alap {bin};
    BinPrinter(std::ostream & os): os{os}{}
    std::ostream & operator<< (int decN) const {
        int msb = 1;
        
        while(msb*2 < decN)
            msb *= 2;
        
        while (msb != 0) {
            os << (char)(decN / msb + '0');
            decN %= msb;
            msb /= 2;
        }
        
        return os;
    }
};

BinPrinter operator<< (std::ostream & os, BinPrinter::alap a){
    return BinPrinter{os};
}

/* --- A) feladat vége */

/* B) feladat: */
class BaseNPrinter{
    std::ostream & os;
    const int base;
public:
    BaseNPrinter(std::ostream & os, int baseN):os{os}, base{baseN}{}
    
    /* feltételezve hogy base(10) -> base(n) konverzió van megengedve csak */
    std::ostream & operator<< (int decN) const {
        int msb = 1;
        
        while(msb*base < decN)
            msb *= base;
        
        while (msb != 0) {
            int digit = decN / msb;
            os << (char)(digit >= 10 ? digit - 10 + 'A' : digit + '0');
            decN %= msb;
            msb /= base;
        }
        
        return os;
    }
};

/* lehetne a Base egy belső osztálya BaseNPrinternek, és akkor használata következő lenne:
 *      main() -ben: std::cout << BaseNPrinter::Base(n)
 *      BaseNPrinter operator<< fejlécében: BaseNPrinter::Base b
 * azért írtam meg külön osztálynak, mert így jobban hasonlít a feladatkiírás példájára */
 
class Base{
    int base;
public:
    explicit Base(int n): base(n) {}
    explicit operator int(){
        return base;
    }
};

BaseNPrinter operator<< (std::ostream & os, Base b){
    return BaseNPrinter{os, (int)b};
}
/* --- B) feladat vége */

int main(int argc, const char * argv[]) {
    std::cout << BinPrinter::bin << 0 << std::endl;
    std::cout << BinPrinter::bin << 240 << std::endl;
    
    std::cout << Base(7) << 240 << std::endl;
    std::cout << Base(2) << 240 << std::endl;
    std::cout << Base(16) << 240 << std::endl;
    return 0;
}
