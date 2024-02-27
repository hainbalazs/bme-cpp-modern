#include <iostream>
#include <type_traits>
#include <cstdint>
#include <string>
#include <ctime>

namespace opt {
    // ha nem a default konstruktorral, így is lehet jelezni "üres értekadást":
    struct nullobj_t {};
    static constexpr nullobj_t nullobj {}; // opt::nullobj
}

template <typename T>
class Optional{
    uint8_t object[sizeof(T)] alignas(std::alignment_of<T>);
    bool hasValue;

    class empty_object: public std::exception{
        virtual const char * what() const noexcept final override  {
            return "Ures objektumot probalsz elerni.";
        }
    };

public:
    // ctor
    Optional(): hasValue{false} {}
    Optional(opt::nullobj_t null): hasValue{false}{}
    Optional(T const & obj):hasValue{true}{
        ::new(object) T(obj);
    }
    Optional(T && tempobj): hasValue{true}{
         ::new(object) T(std::move(tempobj));
    } 

    //copy ctor
    Optional(Optional const & other): hasValue{other.hasValue}{
        if(hasValue)
            ::new(object) T(*other);
    }
    Optional(Optional && tempother): hasValue{tempother.hasValue}{
        if(hasValue)
            ::new(object) T(std::move(*tempother));
    }

    // op=
    Optional& operator=(Optional const & obj){
        if(this != &obj){
            hasValue = obj.hasValue;
            if(hasValue){
                (*obj).~T();           // nem túl szép nyíloperátor nélkül, de ha lenne úgyis csak privát lehetni 
                ::new(object) T(*obj);
            }
        }
        return *this;
    }
    Optional& operator=(Optional && tempobj){
        if(this != &tempobj){
            hasValue = tempobj.hasValue;
            if(hasValue){
                (*tempobj).~T();
                ::new(object) T(std::move(*tempobj));
            }
        }
        return *this;
    }

    T& operator*(){
        if(hasValue)
            return *(reinterpret_cast<T*>(object));
        else 
            throw empty_object();
            
    }

    explicit operator bool() const{
        return hasValue;
    }

    ~Optional(){
        if(hasValue)
            reinterpret_cast<T*>(object)->~T();
    }

}; 

Optional<std::string> get_string() {
    if(rand()%2)
        return opt::nullobj; // return {};
    else 
        return std::string("hello");
}
 
int main() {
    srand(time(nullptr));
    Optional<std::string> opt = get_string();
    if (opt) {
        std::cout << "Ezt a sztringet kaptam: " << *opt << std::endl;
    } else {
        std::cout << "Nem kaptam sztringet" << std::endl;
    }

    Optional<std::string> empty;
    Optional<std::string> hasSomething = std::string("value");

    try{
        std::string whatsInside = *empty;
    }
    catch(std::exception& e){
        std::cout<< e.what() << std::endl;
    }

    empty = std::move(hasSomething);
    
    return 0;
}