#include <iostream>

/* 1. kérdés */

template <typename T>
auto my_make_shared() {
    return std::shared_ptr<T>(new T());
}

/* Mikor egy shared_ptr -nek átadunk egy erőforrást, a fenti szintaszissal inicializálva
   (azaz shared_ptr(T* ptr) konstruktor hívásával)
    annak a jelentése az hogy az okos pointerre bízzuk az erőforrás kezelést.
 * Ilyenkor a referenciák száma 1 lesz, tehát a csak az adott okos pointer felelős a tárolt pointerért.
   így tehát ha shared_ptr konstruktor hívása közben kivétel keletetkezik, neki a felelőssége felszabadítani
   az átvett pointeren keresztül mutatott objektumot, és ezzel nem szegi meg az alap garanciák biztosítását
   a kivételbiztosságra, hiszen ha ez megszegné (pl.: láncolt lista egyik elemét referálnánk ezzel a pointerrel, és ha megszűnne, akkor a lista is tönkremenne), akkor egy egyszerű destruktor hívás is megszegné, hiszen a referenciák száma 1, nem mutat még weak pointer se.
 
 shared_ptr(T* ptr){
    if(ptr)
        try{
        // menedzserObjektumLétrehozása{ kezeltObjektum: ptr, referenciákSzáma: 1 }
        ...
        }
    catch(...){
         delete ptr;
         throw;
    }
 }
 
 */



/* 2. kérdés */
struct X {
    X() = default;
    X(X const &) { throw 0; }
    // X másoló konstruktora garantáltan dobni fog egy int-et
};

/* X-et érték szerint vesszük át, így a függvényhíváskor lemásolódik a paraméter
 * meghívódik a másoló konstruktor, ami kivételt dob
 * de a függvény törzse nem dob kivételt,így az teljesíti a noexcept feltételt
 * azaz nem terminál a program hívásakor.
 */
void f_val(X param) noexcept {
}
/* A függvény törzse meghívja x másoló konstruktorát, ami kivételt dob
 * így nem téve eleget a noexcept jelzőnek
 * ezért f_ref hívásakor a program terminál
 >  libc++abi.dylib: terminating with uncaught exception of type int
 >  Program ended with exit code: 9
 */
void f_ref(X const & param) noexcept {
    X copy(param);
}

int main() {
    X x1;
    
    try {
        std::cout << "f_val hivasa" << std::endl;
        f_val(x1);
    // f_val(x1) *meghívásakor* kivétel keletkezik, ami a catch ágban lekezelődik
    } catch (...) {}
    // emiatt itt folytatódik tovább a program futása
    try {
        std::cout << "f_ref hivasa" << std::endl;
        // híváskor nem keletkezik kivétel, mivel referenciával vesszük át x1-t, ezért lefut a függvénytörzs
        f_ref(x1);
        // ami miatt terminál a program
    } catch (...) {}
}
