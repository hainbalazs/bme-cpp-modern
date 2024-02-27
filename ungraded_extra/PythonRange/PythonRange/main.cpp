//
//  main.cpp
//  PythonRange
//
//  Created by Hain Balázs on 2019. 10. 05..
//  Copyright © 2019. Hain Balázs. All rights reserved.
//

#include <iostream>

class Range {
    int begin_;
    int end_;
    int diff_;
    
public:
    Range(int e): begin_{0}, end_{e}, diff_{1}{}
    Range(int b, int e): begin_{b}, end_{e}, diff_{1}{}
    Range(int b, int e, int d): begin_{b}, end_{e}, diff_{d}{
        if (d == 0)
            throw std::out_of_range("Nem lehet 0 a kulonbseg");
    }
    class iterator{
        int n;
        int diff;
    public:
        iterator(int n, int diff): n{n}, diff{diff}{}
        iterator& operator++() {
            n += diff;
            return *this;
        }
        iterator operator++(int) {
            iterator masolat = *this;
            ++(*this);
            return masolat;
        }
        int operator*() const{
            return n;
        }
        /* ezt használja összehasonlításra a for */
        bool operator!=(iterator rhs) const {
            if(diff > 0)
                return n < rhs.n;
            return n > rhs.n;
        }
    };
    iterator begin(){
        return iterator(begin_, diff_);
    }
    iterator end(){
        return iterator(end_, diff_);
    }
    
};


int main(int argc, const char * argv[]) {
    for (auto i : Range(0, 5))      /* 0 1 2 3 4 */
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : Range(5, 0, -1))  /* 5 4 3 2 1 */
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : Range(5))         /* 0 1 2 3 4 */
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : Range(1, 10, 2))  /* 1 3 5 7 9 */
        std::cout << i << " ";
    std::cout << std::endl;
    try {
        Range(1, 10, 0);            /* a differencia nem lehet 0 */
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
