#include <utility>
#include <tuple>
#include <iostream>
 
struct Time {
    int h, m;
};
 
struct Date {
    int y, m, d;
};
 
bool operator<(Time t1, Time t2) {
    return std::make_pair(t1.h, t1.m) < std::make_pair(t2.h, t2.m);
}
 
bool operator<(Date d1, Date d2) {
    return std::make_tuple(d1.y, d1.m, d1.d) < std::make_tuple(d2.y, d2.m, d2.d);
}
 
int main() {
    std::cout << (Time{12, 15} < Time{13, 05});
    std::cout << (Date{2011, 11, 11} < Date{2012, 11, 12});
}