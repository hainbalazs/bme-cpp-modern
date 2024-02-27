#include <iostream>

class Ratio {
  public:
    Ratio(int num = 0, int den = 1);
    int num() const { return num_; }
    int den() const { return den_; }
    operator double() const;
  private:
    int num_;
    int den_;
};

Ratio::Ratio(int num, int den) {
    /* Euclidean: gcd -> a */
    int a = num, b = den, t;
    while (b != 0)
        t = a%b, a = b, b = t;
    num_ = num/a;
    den_ = den/a;
    /*szebb ha a számláló negatív, és le is egszerûsíti a -a/-b alakú törtet*/
    if(den_ < 0){
        den_ *=-1;
        num_ *=-1;
    }
}

 Ratio::operator double() const {
    return double(num_) / den_;
}

 Ratio operator+(Ratio r) {
    return r; // nem sok mindent csinal
 }

Ratio operator+(Ratio r1, Ratio r2) {
    return Ratio(
        r1.num() * r2.den() + r2.num() * r1.den(),
        r1.den() * r2.den());
}

 Ratio operator-(Ratio r) {
    return Ratio(-r.num(), r.den());
 }

 Ratio operator-(Ratio r1, Ratio r2) {
    return Ratio(
        r1.num() * r2.den() - r2.num() * r1.den(),
        r1.den() * r2.den());
 }

 Ratio operator*(Ratio r1, Ratio r2){
    return Ratio(
        r1.num()*r2.num(),
        r1.den()*r2.den());
 }

  Ratio operator/(Ratio r1, Ratio r2){
    return Ratio(
        r1.num()*r2.den(),
        r1.den()*r2.num());
 }

  Ratio& operator+=(Ratio& r1, Ratio r2){
    r1 = r1 + r2;
    return r1;
 }

 Ratio& operator-=(Ratio& r1, Ratio r2){
    r1 = r1 - r2;
    return r1;
 }
 Ratio& operator*=(Ratio& r1, Ratio r2){
    r1 = r1 * r2;
    return r1;
 }

 Ratio& operator/=(Ratio& r1, Ratio r2){
    r1 = r1 / r2;
    return r1;
 }

std::ostream &operator<<(std::ostream &os, Ratio r) {
    os << r.num() << '/' << r.den();
    return os;
}

 std::istream& operator>>(std::istream& is, Ratio& r) {
    char c;
    int num, den;
    is >> num>> c >> den;
    r = Ratio(num, den);
    return is;
}

int main() {
    Ratio r1(1, 10);
    Ratio r2(5, 10);
    Ratio r3 = r1+r2;
    std::cout << r1 << '+' << r2 << '=' << r3 << std::endl;
    std::cout << r1 << "+=" << r2 << '=' << (r1+=r2) << std::endl;
    std::cout << -r1 << std::endl;
    std::cout << "Irj be egy tortet: ";
    Ratio r4;
    std::cin >> r4;
    std::cout << std::endl << r4;
}
