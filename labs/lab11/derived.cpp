#include <iostream>

template <typename BASE, typename DERIVED>
struct isDerived {
    static constexpr bool f(void* dummy){
        return false;
    }

    static constexpr bool f(BASE* os){
        return true;
    }

    static constexpr bool value = f(static_cast<DERIVED*>(nullptr));
};

class Base {};
class Derived: public Base {};
 
int main() {
    std::cout << isDerived<Base, Derived>::value;    /* 1 */
    std::cout << isDerived<Base, std::ostream>::value;    /* 0 */
}
