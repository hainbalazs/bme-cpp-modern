#include <iostream>
#include <cmath>

double heron(double x){
    auto good_enough = [x](double guess){
        return std::abs(guess*guess - x) < 0.001;
    };
    auto improve = [x](double guess){
        return (guess + x / guess)/2.0;
    };
    double guess = 1.0;
    while(!good_enough(guess))
        guess = improve(guess);
    return guess;
}

int main(){
    std::cout << heron(9);
    return 0;
}