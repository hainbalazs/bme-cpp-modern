#include <iostream>

template <typename T>
class MyStack {
    T* verem;
    size_t capacity;
    size_t siz = 0;


public:
    MyStack(): capacity{0}{
        verem = static_cast<T*> (malloc(sizeof(T)*10));
    }

    /*MyStack(size_t siz): capacity{siz + 10}, siz{siz}{
        verem = static_cast<T*> (malloc(sizeof(T)* capacity));
        for(size_t i = 0; i < siz; i++)
            new (&verem[i]) T();
    }*/

    MyStack(const MyStack& other): capacity{other.capacity}{
        for(auto i : other.verem)
            push(other.verem[i]);
    }
    MyStack& operator=(MyStack& other) = delete;

    void resize(size_t newSize){
        if(newSize > capacity || (newSize < capacity && newSize > siz)){
            T* ujverem = static_cast<T*> (::operator new(sizeof(T)* newSize));
            for(size_t i = 0; i < siz; i++)
                ::new(&ujverem[i]) T(verem[i]);
            for(size_t i = 0; i < siz; i++)
                verem[i].~T();
            ::operator delete(verem);

            verem = ujverem;
            capacity = newSize;
        }
    }

    const T& push(const T& elem){
        if(siz == capacity)
            resize(capacity * 2);
        new (&verem[siz++]) T(elem);
        return verem[siz-1];
    }
    T& pop(){
        if(siz == 0)
            throw std::out_of_range("ures a verem");
         T result = verem[siz--];
        verem[siz+1].~T();
        if(siz < capacity/4)
            resize(capacity*0.5);
    }
};

class Noisy {
  public:
    explicit Noisy(int i) : i_{i} {
        std::cout << "Noisy{" << i << "} ctor\n"; count++;
    }
    Noisy(Noisy const &o) : i_{o.i_} {
        std::cout << "Noisy copy ctor " << i_ << "\n"; count++;
    }
    Noisy& operator=(Noisy const &o) = delete;
    ~Noisy() {
        std::cout << "Noisy dtor " << i_ << "\n"; count--;
        i_ = rand();    /* ! */
    }
    static void report() {
        std::cout << count << " instance(s).\n";
    }
  private:
    int i_;
    static int count;
};

int Noisy::count = 0;


int main()
{
    MyStack<Noisy> verem;
    std::cout << "------------" << std::endl;
    for(int i = 0; i < 15; i++)
        verem.push(Noisy{i});

    return 0;
}
