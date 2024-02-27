#include <iostream>

class TimeInterval{
    int minute;
public:
    TimeInterval(int t): minute{t}{}
    operator int(){
        return minute;
    }
    int getMinute(){
        return minute;
    }

};
std::ostream & operator<<(std::ostream & os, TimeInterval t){
    os << t/60 << "h " << t%60 << "m ";
    return os;
}
TimeInterval operator "" _m(unsigned long long m){
    return TimeInterval(m);
}
TimeInterval operator "" _h (unsigned long long h){
    return TimeInterval(h*60);
}
int main()
{
    TimeInterval i1{65};
    std::cout << i1 << std::endl;

    TimeInterval i2 = 5_h + 79_m;
    std::cout << i2 << std::endl;
}
