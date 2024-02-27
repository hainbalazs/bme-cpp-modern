#include <iostream>
#include <iterator>
#include <functional>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <vector>

class Noisy {
  private:
    int data;           /* csak hogy legyen-e benne valami */

    /* példányok kezeléséhez */
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

    ~Noisy() noexcept(false) { /* dtor nem kéne dobjon, de most fog. az élet nem habostorta. */
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
void merge(T& in, typename T::iterator begin, typename T::iterator mid, typename T::iterator end, T& out) {
    auto i = begin, j = mid;
    for (auto c = begin; c < end; ++c) {
        if (i < mid && (j >= end || (*i <= *j))) { // noisyban osszehasonlito op kell
                //iterator most hogyan? kié?
            out[c] = std::move(*i); //placement new kell
            i++;
        } else {
            out[c] = std::move(*j); //ide is
            j++;
        }
    }
}

 template <typename T>
void copy(T& in, typename T::iterator begin, typename T::iterator end, T& out) {
    in = std::move(out);
}
 template <typename T>
void merge_sort(T& tomb, typename T::iterator begin, typename  T::iterator end, T& temp) {
    if (end - begin < 2)
        return;

    auto mid = begin + std::distance(begin, end) / 2;

    merge_sort(tomb, begin, mid, temp);
    merge_sort(tomb, mid, end, temp);
    merge(tomb, begin, mid, end, temp);
    copy(temp, begin, end, tomb);
}

template <typename T>
void merge_sort_start(T& tomb){
    auto begin = std::begin(tomb);
    auto end = std::end(tomb);

    void *mem = ::operator new(sizeof(T));
    T* segedTomb = static_cast<T*>(mem);
    merge_sort(tomb, begin, end, *segedTomb);
    ::operator delete(mem);

}

int main (){

    std::vector<Noisy> noisyVector = {Noisy(5), Noisy(2), Noisy(4), Noisy(1), Noisy(3)};
    merge_sort_start(noisyVector);
    return 0;
}
