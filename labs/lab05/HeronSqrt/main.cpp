#include <iostream>

class Heron{
    double sq;
    bool good_enough(double guess){
        return abs(guess*guess - sq) < 0.001;
    }
    double improve(double guess){
        return (guess + (double)sq/guess)/2.0;
    }
public:
    double get(double square){
        sq = square;
        double guess = 1.0;
        while(!good_enough(guess))
            guess = improve(guess);
        return guess;
    }
};

int main()
{
    Heron h;
    std::cout << h.get(4.0);
    return 0;
}
