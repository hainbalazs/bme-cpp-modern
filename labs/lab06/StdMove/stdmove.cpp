#include <iostream>
#include <iomanip>
#include <algorithm>

#define MOVE

class Matrix {
public:
    /* default, [w*h] mérettel hívható ctor */
    Matrix(): w_(0), h_(0), data_(nullptr){
        std::cout << "default ctor" << std::endl;
    }
    Matrix(size_t w, size_t h): w_(w), h_(h), data_(new double [w*h]){
        std::cout << "with size [w*h] ctor" << std::endl;
        for(size_t i = 0; i < w_*h_; i++)
            data_[i] = 0;
    }
    
    /* másoló, mozgató ctor */
    Matrix(Matrix const & ref): w_(ref.w_), h_(ref.h_), data_(new double[w_*h_]){
        std::cout << "copy ctor" << std::endl;
        for(size_t i = 0; i < w_*h_; i++ ){
            data_[i] = ref.data_[i];
        }
    }
    #ifdef MOVE
    Matrix(Matrix && ref):w_(ref.w_), h_(ref.h_), data_(ref.data_){
        std::cout << "move ctor" << std::endl;
        ref.data_ = nullptr;
    }
    #endif
    
    /* értékadó operátor, move assignment operator */
    Matrix& operator=(Matrix const & ref){
        std::cout << "assignment operator" << std::endl;
        if(this != &ref){
            delete data_;

            w_ = ref.w_;
            h_ = ref.h_;
            data_ = new double[w_*h_];
            for(size_t i = 0; i < w_*h_; i++ ){
            data_[i] = ref.data_[i];
            }
        }
        return *this;
    }
    #ifdef MOVE
    Matrix& operator=(Matrix && ref){
        std::cout << "move assignment operator" << std::endl;
        if(this != &ref){
            delete data_;
            data_ = ref.data_;
            ref.data_ = nullptr;
            w_ = ref.w_;
            h_ = ref.h_;

            ref.w_ = 0;
            ref.h_ = 0;
        }
        return *this;
    }
    #endif

    double& operator()(size_t i, size_t j){
        if(j < 1 || i < 1 || i > w_ || j > h_ )
            throw(std::out_of_range("Túlindexelés!"));
        return data_[(j-1)*w_ + (i-1)];
    }

    double operator()(size_t i, size_t j) const{
        if(j < 1 || i < 1 || i > w_ || j > h_ )
            throw(std::out_of_range("Túlindexelés!"));
        return data_[(j-1)*w_ + (i-1)];
    }

    /* méret getterek */
    size_t getW() const {return w_;}
    size_t getH() const {return h_;}

    /* operator+ */
    Matrix operator+(Matrix const & ref) {
        if(this->w_ != ref.w_ || this->h_ != ref.h_)
            throw (std::logic_error("Nem egyezik meg a mátrixok méretei"));
        
        Matrix result(w_, h_);
        for(size_t i = 0; i < w_*h_; i++ ){
            result.data_[i] = data_[i] + ref.data_[i];
        }
        return result;
    }


    /* dtor */
    ~Matrix(){
        std::cout << "dtor" << std::endl;
        delete[] data_;
    }
private: 
    size_t w_, h_;
    double *data_;
};

std::ostream & operator<<(std::ostream& os, Matrix const & mx){
    for(size_t i = 1; i <= mx.getW(); i++) {
        for(size_t j = 1; j <= mx.getH(); j++){
            os << std::setw(5) << mx(i, j);
        }
        os << std::endl;
    }
    return os;
}

Matrix&& operator+(Matrix&& rv, Matrix & lv){
     if(lv.getW() != rv.getW() || lv.getH() != rv.getH())
            throw (std::logic_error("Nem egyezik meg a mátrixok méretei"));

    for(size_t i = 1; i <= lv.getW(); i++)
        for(size_t j = 1; j <= lv.getH(); j++)
            rv(i, j) += lv(i, j); 
    
    return std::move(rv);
}

Matrix&& operator+(Matrix& lv, Matrix && rv){
    return (std::move(rv) + lv);
}

Matrix&& operator+(Matrix&& rv1, Matrix &&rv2){
    return (std::move(rv1) + rv2);
}

int main(){
    Matrix m1{3,3};
    m1(1, 1) = 9; m1(2, 3) = 5;
    std::cout << "Mátrix1: " << std::endl << m1 <<std::endl;

    Matrix m2{3,3};
    m2(2, 2) = 2; m2(3, 1) = 3;
    std::cout << "Mátrix2: " << std::endl << m2 <<std::endl;

    Matrix m3{3,3};
    m3(3,3) = 69; m3(2, 2) = 4.5; m3(1, 2) = 23;
    std::cout << "Mátrix3: " << std::endl << m3 <<std::endl;

    Matrix m4{3,3};
    std::cout << "Mátrix4: " << std::endl << m4 <<std::endl;

    std::cout << "STD::SWAP ----------------" << std::endl;
    std::swap(m1, m2);
    std::cout << "---------------- STD::SWAP" << std::endl;

    std::cout << (m1 + (m2 + m3));
}