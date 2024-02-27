#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>

template <typename VALUETYPE>
class Solver {
  public:
    /* VariableValueFunc: ez azt a változót reprezentálja, amely tesztelés
     * közben különféle értékeket vesz fel. Ha meghívjuk a függvényt,
     * megkapjuk az értéket. */
    using VariableValueFunc = std::function<VALUETYPE const &()>;
    /* ConstraintFunc: egy olyan paraméter nélküli függvény, amely megmondja,
     * hogy az elvárt összefüggések épp teljesülnek-e. */
    using ConstraintFunc = std::function<bool()>;
    /* ActivityFunc: ilyen függvényt fog meghívni a Solver, amikor tesztelés
     * közben talál egy megoldást. */
    using ActivityFunc = std::function<void()>;


  private:
    /* Ezeket a változókat kell vizsgálni */
    std::vector<std::vector<VALUETYPE>> variables_;
    /* Ez meg a vizsgálat közben fog kelleni */
    std::vector<typename std::vector<VALUETYPE>::const_iterator> iterators_;
    /* Ezen feltételek szerint fog futni a vizsgálat */
    std::vector<ConstraintFunc> constraints_;
  
  public:
    /* Egy változó lehetséges értékeit tartalmazó tárolót várja.
     * Ad egy olyan függvényt vissza, amelyet meghívva
     * lekérdezhető, hogy a tesztelés közben az adott változónak éppen
     * mi az értéke. A használó ezekre a függvényekre tud majd építeni.
     * Az iterátorok egyelőre nem léteznek, úgyhogy nem tudjuk az iterátor
     * referenciáját eltárolni. */
    VariableValueFunc add_variable(std::vector<VALUETYPE> values) {
        if (values.empty())
            throw std::runtime_error("add_variable: a lehetseges ertekek halmaza nem lehet ures");
        for (size_t i = 0; i < values.size() - 1; ++i)
            for (size_t j = i+1; j < values.size(); ++j)
                if (values[i] == values[j])
                    throw std::runtime_error("add_variable: egyforma elemek is vannak a taroloban");
        variables_.push_back(std::move(values));
        size_t pos = variables_.size()-1;
        return [this, pos] () -> VALUETYPE const & {
            return *iterators_[pos];
        };
    }

    /* Feltétel hozzáadása. A feltétel egy függvény, amely igaz értéke
     * esetén az aktuális állapot elfogadható. */
    void add_constraint(ConstraintFunc constraint) {
        constraints_.push_back(std::move(constraint));
    }

    /* Teszteli az összes lehetséges értéket, és amikor olyan
     * állapotban vannak az iterátorok, amik épp egy elfogadható
     * kombinációra mutatnak, akkor meghívja a függvényt. */
    void solve(ActivityFunc do_what) {
        /* iterátorok inicializálása */
        iterators_.clear();
        for (auto & v : variables_)
            iterators_.push_back(v.begin());

        /* A Variable-k current iterátorait már mind begin-re
         * állítottuk, szóval most az elején áll az összes. */
        bool end = false;
        while (!end) {
            /* Jó az aktuális állapot? Ha mindegyik igazat ad. */
            bool satisfied = std::all_of(
                constraints_.begin(), constraints_.end(),
                [] (ConstraintFunc const & cons) { return cons(); }
            );
            /* Ha mindegyik Constraint szerint jó az aktuális megoldás: */
            if (satisfied)
                do_what();

            /* Következőre ugrás: a digit teljes összeadója kódban. */
            bool carry = true;
            for (size_t i = 0; i < variables_.size(); ++i) {
                ++iterators_[i];
                carry = iterators_[i] == variables_[i].end();
                if (carry)
                    iterators_[i] = variables_[i].begin();
                else
                    break;
            }
            /* Ha vége lett, és még mindig carry=true, körbeértünk. */
            end = carry;
        }
        
        /* ezek már nem kellenek */
        iterators_.clear();
    }
};

int main(){
    std::vector<int> szamok(100);
    for(int i = 0; i <= 100; i++)
        szamok[i] = i;

    Solver<int> pitagorasz;

    auto a = pitagorasz.add_variable(szamok);
    auto b = pitagorasz.add_variable(szamok);
    auto c = pitagorasz.add_variable(szamok);

    pitagorasz.add_constraint([=]{return b() > a();});
    pitagorasz.add_constraint([=]{return c() > b();});
    pitagorasz.add_constraint([=]{return a()*a() + b()*b() == c()*c();});
    int count = 0;
    pitagorasz.solve([&count] () mutable {
        ++count;
    });
    std::cout << count << std::endl;

    // -------------------------------------------------

    Solver<int> euler;

    auto sertes = euler.add_variable(szamok);
    auto kecske = euler.add_variable(szamok);
    auto juh = euler.add_variable(szamok);

    euler.add_constraint([=]{return sertes() + kecske() + juh() == 100;});
    euler.add_constraint([=]{return sertes()*21 + kecske()*8 + juh()*3 == 600;});

    euler.solve([=]{std::cout<<"sertes: "<< sertes() << " kecske: " << kecske() << " juh: " << juh() << std::endl;});

    // ---------------------------------------------------
    enum colors {kek, sarga, piros};
    Solver<colors> map;
    

    auto A = map.add_variable({kek, sarga, piros});
    auto B = map.add_variable({kek, sarga, piros});
    auto C = map.add_variable({kek, sarga, piros});
    auto D = map.add_variable({kek, sarga, piros});
    auto E = map.add_variable({kek, sarga, piros});

    map.add_constraint([=]{return D() < E();});
    map.add_constraint([=]{return B() < A();});
    map.add_constraint([=]{return A() != C() && A() != E() && A() != D();});
    map.add_constraint([=]{return B() != C() && B() != D();});
    map.add_constraint([=]{return E() != C();});

    map.solve([=]{std::cout << "A: " << A() << " B: " << B() << " C: " << C() << " D: " << D() << " E: " << E();});

    // ----------------------------------------------------------------

    Solver<int> queens;
    std::vector<std::function<const int&()>> q(8);
    for(int db = 0; db < 8; db++)
        q[db] =queens.add_variable({1,2,3,4,5,6,7,8});
                
    queens.add_constraint([q]{
        bool b = true;
        for(int j = 0; j < 8; j++)
            for(int i = j+1; i < 8; i++)
                b = b && (q[i]() != q[j]());

        return b;
    });
        

    for(int j = 0; j < 8; j++)
        for(int i = j+1; i < 8; i++){
            queens.add_constraint([q, i, j]{return q[i]() - q[j]() != i - j;});
        }
    
    count = 0;
    queens.solve([&count] () mutable {++count;} );
    std::cout << count << std::endl;

    return 0;
}