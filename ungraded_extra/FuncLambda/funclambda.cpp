#include <iostream>
#include <functional>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>

std::function<double(double)> create_func_from_rpn(std::string expr){
    std::stack<std::function<double(double)>> stack;
    std::string s;
    std::istringstream iss(expr);

    while(iss >> s){
        if(isdigit(s[0]))
            stack.push([s](double d) -> double {return std::stoi(s);});
        else if(s[0] == 'x')
            stack.push([](double d) -> double {return d;});
        else{ 
            if(stack.empty()) throw std::logic_error("Hibás a megadott kifejezés!");

            auto op1 = std::move(stack.top());
            stack.pop();
            auto op2 = std::move(stack.top());
            stack.pop();
            switch(s[0]){
                case '+':
                stack.push([op1, op2](double d) -> double{return op1(d) + op2(d);});
                break;
                case '-':
                stack.push([op1, op2](double d) -> double{return op1(d) - op2(d);});
                break;
                case '/':
                stack.push([op1, op2](double d) -> double{return op1(d) / op2(d);});
                break;
                case '*':
                stack.push([op1, op2](double d) -> double{return op1(d) * op2(d);});
                break;
                default: throw std::logic_error("Hibás a megadott kifejezés!");
            }
        }
    }
    return stack.top();
}

int main(){
    auto f = create_func_from_rpn("15 7 1 1 + - / x * 2 1 1 + + -");   // f = 21+34*x
 
    std::cout << f(-3) << std::endl;                 // 21+34*3 értéke

    try{
        auto f = create_func_from_rpn("kolbász kenyér +");
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}