#include <iostream>
#include <iomanip>
#include <cmath>

template <typename F>
class Derival{
    F func;
public:
    Derival(F f): func(f){}
    double operator()(double arg) const {
        double dx = 0.001;
        return (func(arg + dx) - func(arg)) / dx;
    }
};

class Parabola{
    double a_;
    double b_;
    double c_;
public:
    Parabola(double a, double b, double c): a_{a}, b_{b}, c_{c}{}
    double operator()(double x) const {
        return a_*x*x + b_*x + c_;
    }
};

int main() {
    Derival<double (*) (double)> my_cos = Derival<double (*) (double)>{sin};
    for (double f = 0; f < 3.1415; f += 0.1)
        std::cout << std::setw(20) << my_cos(f)-cos(f) << std::endl;


    Parabola p1{0.5, 2.3, -5};  /* 0.5x^2 + 2.3x - 5 */
    auto p1_der = Derival<Parabola> {p1};

    Parabola p2{0, 1, 2.3};     /* x + 2.3, p1 deriváltja */
    for (double f = 0; f < 3.0; f += 0.1)
        std::cout << std::setw(20) << p1_der(f)-p2(f) << std::endl;

    return 0;
}
