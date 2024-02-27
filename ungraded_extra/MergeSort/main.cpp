//
//  main.cpp
//  MergeSort
//
//  Created by Hain Balázs on 2019. 10. 19..
//  Copyright © 2019. Hain Balázs. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>
#include <ctime>

class Noisy {
  private:
    int data;           /* csak hogy legyen-e benne valami */

    /* p�ld�nyok kezel�s�hez */
    static std::set<Noisy const*> constructed;
    static std::set<Noisy const*> valid;
    static bool is_valid(Noisy const *n) {
        return valid.count(n) == 1;
    }
    static bool is_constructed(Noisy const *n) {
        return constructed.count(n) == 1;
    }


  public:
    static bool noisy;  /* osszes ctor es dtor kiir-e kimenetre */

    int get_data() const {
        if (!is_valid(this))
            throw std::logic_error("Nem letezo objektum get_data-ja");
        return data;
    }

    Noisy(int i = 0) {
        if (is_constructed(this))
            throw std::logic_error("Letezo objektumra hivsz konstruktort");
        constructed.insert(this);
        valid.insert(this);
        data = i;
        if (noisy)
            std::cerr << "Noisy letrehozva @" << this << std::endl;
    }

    Noisy(Noisy const & o) {
        if (is_constructed(this))
            throw std::logic_error("Letezo objektumra hivsz konstruktort");
        if (!is_valid(&o))
            throw std::logic_error("Ures vagy nem letezo objektumot akarsz lemasolni");
        constructed.insert(this);
        valid.insert(this);
        data = o.data;
        if (noisy)
            std::cerr << "Noisy masolva ide @" << this << " innen @" << &o << std::endl;
    }

    Noisy(Noisy && o) {
        if (is_constructed(this))
            throw std::logic_error("Letezo objektumra hivsz konstruktort");
        if (!is_constructed(&o))
            throw std::logic_error("Nem letezo objektumot akarsz mozgatni");
        constructed.insert(this);
        if (is_valid(&o)) {
            valid.insert(this);
            valid.erase(&o);
        }
        data = o.data;
        o.data = -1;
        if (noisy)
            std::cerr << "Noisy mozgatva innen @" << &o << " ide @" << this << std::endl;
    }

    ~Noisy() noexcept(false) { /* dtor nem k�ne dobjon, de most fog. az �let nem habostorta. */
        if (!is_constructed(this)) {
            throw std::logic_error("Nem letezo objektumra hivsz destruktort");
        }
        constructed.erase(this);
        valid.erase(this);
        if (noisy)
            std::cerr << "Noisy megszunt itt @" << this << std::endl;
    }

    Noisy& operator=(Noisy const &o) {
        if (!is_constructed(this))
            throw std::logic_error("Nem letezo objektum operator=-jet hivtad");
        if (!is_valid(&o))
            throw std::logic_error("Ures vagy nem letezo objektumbol akarsz erteket adni");
        data = o.data;
        valid.insert(this);
        if (noisy)
            std::cerr << "Noisy masolo ertekadas ide @" << this << " innen @" << &o << std::endl;
        return *this;
    }

    Noisy& operator=(Noisy && o) {
        if (!is_constructed(this))
            throw std::logic_error("Nem letezo objektum operator=-jet hivtad");
        if (!is_constructed(&o))
            throw std::logic_error("Nem letezo objektumot akarsz mozgatni");
        if (is_valid(&o)) {
            valid.insert(this);
            valid.erase(&o);
        } else {
            valid.erase(this);
        }
        data = o.data;
        o.data = -1;
        if (noisy)
            std::cerr << "Noisy mozgato ertekadas innen @" << &o << " ide @" << this << std::endl;
        return *this;
    }

    static size_t get_constructed_count() {
        return constructed.size();
    }
    static size_t get_valid_count() {
        return valid.size();
    }

    friend std::ostream &operator<<(std::ostream &os, Noisy const& n);
    friend std::istream &operator>>(std::istream &is, Noisy & n);
};

std::set<Noisy const*> Noisy::constructed;
std::set<Noisy const*> Noisy::valid;
bool Noisy::noisy = true;

bool operator<=(Noisy const & r1, Noisy const & r2) {
    return r1.get_data() <= r2.get_data();
}

std::ostream &operator<<(std::ostream &os, Noisy const& n) {
    if (!Noisy::is_valid(&n)) {
        throw std::logic_error("Ures vagy nem letezo objektumot akarsz kiirni");
    }
    os << n.data;
    return os;
}

std::istream &operator>>(std::istream &is, Noisy & n) {
    if (!Noisy::is_valid(&n)) {
        throw std::logic_error("Ures vagy nem letezo objektumba akarsz olvasni");
    }
    is >> n.data;
    return is;
}

template <typename T>
void merge(T *in, int begin, int mid, int end, T *out) {
    int i = begin, j = mid;
    for (int c = begin; c < end; ++c) {
        if (i < mid && (j >= end || in[i] <= in[j])) {
            // placement new használata kéne az első inicializálatlan területre való másolásnál
            new (&out[c]) 	T(std::move(in[i]));
            // kell a destruktor hívás mert még mindig "él" az objektum
            in[i].~T();
            i++;
        } else {
            new (&out[c])     T(std::move(in[j]));
            in[j].~T();
            j++;
        }
    }
}

template <typename T>
void copy(T *in, int begin, int end, T *out) {
    for (int c = begin; c < end; ++c) {
        new (&out[c]) T(std::move(in[c]));
        in[c].~T();
    }
}

template <typename T>
void merge_sort(T *tomb, int begin, int end, T *temp) {
    if (end - begin < 2)
        return;
    int mid = (begin + end) / 2;
    merge_sort(tomb, begin, mid, temp);
    merge_sort(tomb, mid, end, temp);
    merge(tomb, begin, mid, end, temp);
    copy(temp, begin, end, tomb);
}

template <typename T>
void merge_sort_start(T *tomb, int begin, int end){
    // intervallum [begin, end) ezért nem kell a +1 méret
    void *mem = ::operator new(sizeof(T)*(end-begin));
    T* temp = static_cast<T*>(mem);
    
    merge_sort(tomb, begin, end, temp);
    
    ::operator delete(mem);
}

int main(int argc, const char * argv[]) {
    Noisy *noisyArr = new Noisy[4]; 
    
    std::cout << "Rendezes elott: ";
    srand(time(0));
    for(size_t i = 0; i < 4; i++){
        noisyArr[i] = rand() % 100;
        std::cout << noisyArr[i] << " ";
    }
    std::cout << "--- RENDZES ---" << std::endl;

    merge_sort_start(noisyArr, 0, 4);
    
    std::cout << std::endl << "Rendezes utan: ";
    for(size_t i = 0; i < 4; i++)
        std::cout << noisyArr[i] << " ";

    delete[] noisyArr;

    return 0;
}
