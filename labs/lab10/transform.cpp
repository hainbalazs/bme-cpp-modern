#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
 
int main() {
    std::vector<double> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    double multiplier = 2.0;

    std::transform(v.begin(), v.end(), v.begin(), std::bind(std::multiplies<double>{}, std::placeholders::_1, multiplier));
    
    for (auto i : v)
        std::cout << i << std::endl;

}
