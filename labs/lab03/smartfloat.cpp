#include <iostream>
#include <cmath>

class Float{
    float data;
    static double precision;
public:
    Float(float f): data{f}{}
    explicit operator float() const {
        return data;
    }
    double getPrecision() {return precision;}

};

double Float::precision = 0.0001;

bool operator<(Float f1, Float f2){
    return (float)f1 < (float)f2 - f1.getPrecision();
}

bool operator>(Float f1, Float f2){
    return f2 < f1;
}

bool operator==(Float f1, Float f2){
    return !(f1 > f2) && !(f1 < f2);
}

bool operator!=(Float f1, Float f2){
    return !(f1 == f2);
}

bool operator<=(Float f1, Float f2){
    return (f1 < f2) || (f1 == f2);
}

bool operator>=(Float f1, Float f2){
    return (f1 > f2) || (f1 == f2);
}

Float operator+(Float f1, Float f2){
    return Float((float)f1+(float)f2);
}

Float operator+(Float f){
    return f;
}

Float operator-(Float f1, Float f2){
    return Float((float)f1-(float)f2);
}

Float operator-(Float f){
    return Float(-(float)f);
}

Float& operator+=(Float &f1, Float f2){
    f1 = f1+f2;
    return f1;
}
Float& operator-=(Float &f1, Float f2){
    f1 = f1-f2;
    return f1;
}

std::ostream & operator<< (std::ostream &os, Float f){
    os << (float) f;
    return os;
}

int main()
{
    Float f1 = 1.0f,
          f2 = 1.00001f,
          f3 = 100;


    std::cout << (f1 < f2) << std::endl;
    std::cout << (f1 < f3) << std::endl;

    f1 = f2 + f3;

    for (Float f = 0.999; f < 1.001; f += 0.0001) {
        std::cout << f << '\t' << (f < 1.0) << std::endl;
    }

    std::cout << -f1;

    return 0;
}
