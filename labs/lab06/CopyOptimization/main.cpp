#include <iostream>
 
// -fno-elide-constructors

class Noisy {
  public:
    Noisy() { std::cout << "Noisy ctor\n"; }
    ~Noisy() { std::cout << "Noisy dtor\n"; }
    Noisy(Noisy const &) { std::cout << "Noisy copy\n"; }
    Noisy(Noisy &&) noexcept { std::cout << "Noisy move\n"; }
};


Noisy create_noisy_on_return() {
    return Noisy();
}

Noisy create_noisy_from_local() {
    Noisy y;
    return y;
}

Noisy create_noisy_with_move() {
    Noisy y;
    return std::move(y);    /* ilyet nem �runk!!! de mi�rt? */
}

void do_something_with_noisy_cref(Noisy const &y) {
}

void do_something_with_noisy_value(Noisy y) {
}

void do_something_with_noisy_rref(Noisy && y) {
}

int main() {
    std::cout << "create_noisy_on_return()\n";
    create_noisy_on_return();
    std::cout << "create_noisy_from_local()\n";
    create_noisy_from_local();
    std::cout << "create_noisy_with_move()\n";
    create_noisy_with_move();

    std::cout << "do_something_with_noisy_cref()\n";
    do_something_with_noisy_cref(Noisy());
    std::cout << "do_something_with_noisy_value()\n";
    do_something_with_noisy_value(Noisy());
    std::cout << "do_something_with_noisy_rref()\n";
    do_something_with_noisy_rref(Noisy());
}
