//
//  main.cpp
//  MyFunction
//
//  Created by Hain Balázs on 2019. 11. 29..
//  Copyright © 2019. Hain Balázs. All rights reserved.
//

#include <functional>
#include <iostream>
#include <cmath>
#include <memory>
#include <utility>

template <typename>
class MyFunction{};

template <typename R, typename ... ARGS>
class MyFunction<R(ARGS...)>{
    class wrapperBase{
    public:
        virtual R operator()(ARGS && ...) const = 0;
        virtual std::unique_ptr<wrapperBase> clone() const = 0;
        virtual ~wrapperBase(){}
    };
    
    template <typename FN>
    class wrapper : public wrapperBase{
    public:
        FN function;
        wrapper(FN f): function{std::move(f)}{}
        virtual std::unique_ptr<wrapperBase> clone() const final override {
            return std::make_unique<wrapper>(*this);
        }
        virtual R operator()(ARGS && ... args) const final override {
            return function(args...);
        }
    };
   
    std::unique_ptr<wrapperBase> pFunc;
    
public:
    MyFunction(): pFunc{nullptr}{}
    MyFunction(std::nullptr_t null): pFunc{nullptr}{}
    
    template <typename FN>
    MyFunction(FN const & func){
        pFunc = std::make_unique<wrapper<FN>>(func);
    }

    MyFunction(MyFunction const &f) {
        pFunc = f.pFunc->clone();
    }
    
    MyFunction& operator=(MyFunction f){
        std::swap(pFunc, f.pFunc);
        return *this;
    }
    
    operator bool(){
        return (pFunc != nullptr);
    }
    
    R operator()(ARGS && ... args){
        if(!*this)
            throw std::bad_function_call();
        
        return (*pFunc)(std::forward<ARGS ...>(args...));
    }
    
    ~MyFunction() = default;
};


int main() {
    MyFunction<double(double)> f;
    
    if (!f)
        std::cout << "Egyelőre nullptr" << std::endl;
    
    f = (double(*)(double)) sin;
    std::cout << sin(2.3) << "==" << f(2.3) << std::endl;
    
    f = [] (double x) { return x*x; };
    std::cout << 2.3*2.3 << "==" << f(2.3) << std::endl;
    
    f = std::bind((double(*)(double, double))pow, std::placeholders::_1, 4);
    std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;
    
    auto f2 = f;    /* másolható */
    std::cout << pow(2.3, 4) << "==" << f2(2.3) << std::endl;
    
    f = nullptr;
    try {
        f(2.3);
    } catch (std::bad_function_call &e) {
        std::cout << "Megint nullptr" << std::endl;
    }
}
