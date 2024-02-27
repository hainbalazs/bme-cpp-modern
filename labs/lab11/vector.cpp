#include <iostream>

struct IndexDontCare{
    template <typename T, typename STRAT>
    static constexpr void check_index(size_t& idx, size_t size, Vector<T, STRAT> const & vector){};
};

struct IndexThrow{
    template <typename T, typename STRAT>
    static constexpr void check_index(size_t& idx, size_t size, Vector<T, STRAT> const & vector){
        if(idx >= size) throw std::invalid_argument("Tulindexeles!");
    };
};

struct IndexTurnBack{
    template <typename T, typename STRAT>
    static constexpr void check_index(size_t& idx, size_t size, Vector<T, STRAT> const & vector){
        idx = idx % size;
    };
};

struct IndexResize{
    template <typename T, typename STRAT>
    static constexpr void check_index(size_t& idx, size_t size, Vector<T, IndexResize> const & vector){
        if(idx >= size)
            vector.resize(idx + 1);
    };
};


template <typename T, class IndexStrategy = IndexDontCare>
class Vector {
  private:
    size_t size;
    T* data;
    
  public:
    explicit Vector(size_t size)
      : size{size}
      , data{new T[size]} {
    }

    void resize(size_t newSize){
        Vector resized(newSize);
        for(size_t i = 0; i < size; i++)
            resized[i] = this[i];
        std::swap(data, resized.data);
        std::swap(size, resized.size);
    }

    Vector(Vector const &) = delete; /* lusta */
    Vector& operator=(Vector const &) = delete; /* lusta */
    ~Vector() {
        delete[] data;
    }
    
    T& operator[](size_t idx) {
        IndexStrategy::check_index(idx, size, *this);
        return data[idx];
    }
};



 
int main() {
    Vector<int, IndexTurnBack> v1(10);
    try{
        v1[0] = 0;
        v1[10] = 3;
    }
    catch(std::exception& e){
        std::cout << e.what();
    }
    std::cout << v1[0];
    return 0;
}
