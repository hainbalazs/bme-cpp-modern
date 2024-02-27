#include <iostream>
#include <vector>
#include <cmath>


class functor {
protected:
    double d;
public:
    functor(double _d): d(_d){}
    virtual double f(double x) = 0;
};

 class SinDTimes : public functor{
public:
   SinDTimes(double _d): functor(_d){}
    double f(double x){
        return sin(d*x);
   }
 };

 class Page {
     int W, H;
     std::vector<std::vector<char>> tomb;
public:
    Page(int _w, int _h): W(_w), H(_h), tomb(_h, std::vector<char>(_w)){
    }
    void print(){
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x)
                std::cout << tomb[y][x];
            std::cout << std::endl;
        }
    }
    void clear(){
        for (int y = 0; y < H; ++y)
            for (int x = 0; x < W; ++x)
                tomb[y][x] = ' ';
    }
    void setchar(int idxH, int idxW, char c){
        tomb[H][W] = c;
    }
    int getWidth(){
        return W;
    }
    int getHeight(){
        return H;
    }
    ~Page(){}
 };

void plot(Page &p, char c, functor& func) {
    int W = p.getWidth(), H = p.getHeight();
    for (int x = 0; x < W; ++x) {
        double fx = (x - W/2)/4.0;
        double fy = func.f(fx);
        int y = (fy * 4.0) * -1 + H/2;
        if (y >= 0 && y < H)
            p.setchar(y, x, c);
    }
}


int main() {

    // tetszõleges fv bõvítésére általam választott megoldás lenne:
    // VLA Tömb paraméter átadás, a szögfv tagokra, speciális esetekre külön fv, mint a dsin-nél
    double d;
    std::cout << "sin(d * x), d = ?" << std::endl;
    std::cin >> d;

    SinDTimes f(d);
    Page p(40, 20);
    std::cout << p.getHeight() << "+" << p.getWidth() << std::endl;
    p.clear();
    std::cout << "kesz";
    plot(p, '*', f);
    std::cout << "ittB";
    p.print();
    std::cout << "ittC";

}
